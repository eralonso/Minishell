/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:56:31 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/17 12:03:10 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	kill_childs(pid_t *pids, int size)
{
	int	i;
	
	i = -1;
	while (++i < size)
		kill(pids[i], SIGTERM);
	return (1);
}

int	wait_childs(pid_t *pids, int size)
{
	int		status;
	int		aux;
	int		i;

	i = -1;
	while (++i < size)
	{
		aux = waitpid(-1, &status, NULL);
		if (aux == -1)
			return (kill_childs(pids, size));
		if (WIFEXITED(status) && aux == pids[size - 1])
			g_msh.err = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				g_msh.err = 130;
			else if (WTERMSIG(status) == SIGQUIT)
				g_msh.err = 131;
		}
	}
	return (0);
}

pid_t	exec_node(t_lstt *node, int idx, int end)
{
	pid_t	child;

	expand_redir(&node);
	child = fork();
	if (child < 0)
		return (ERR_NODE);
	if (child == 0)
		exec_cmd(node->content);
	return (child);
}

int	exec_nodes(t_lstt **node, int size)
{
	t_lstt	*tmp;
	pid_t	*pids;
	int		i;

	if (!node || !*node)
		return (1);
	pids = ft_calloc(sizeof(pid_t), size);
	if (!pids)
		return (1);
	tmp = *node;
	i = -1;
	while (tmp)
	{
		pids[++i] = exec_node(node, i, (i == (size - 1)));
		if (pids[i] == ERR_NODE)
		{
			kill_childs(pids, size);
			free(pids);
			return (1);
		}
		tmp = tmp->next;
	}
	i = wait_childs(pids, size);
	free(pids);
	return (i);
}

int	executor(t_stair *st)
{
	if (!st)
		return (0);
	if (st->type != MAIN)
		if (executor(st->step))
			return (1);
	if ((st->type == AND && g_msh.err) || (st->type == OR && !g_msh.err))
		return (0);
	if (exec_nodes(&st->node, st->size))
		return (1);
	return (0);
}
