/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:56:31 by eralonso          #+#    #+#             */
/*   Updated: 2023/08/03 14:06:23 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	kill_childs(pid_t *pids, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pids[i] > 1)
		{
			kill(pids[i], SIGTERM);
			pids[i] = 0;
		}
	}
	return (1);
}

int	wait_childs(pid_t *pids, int size)
{
	int		status;
	int		aux;
	int		i;
	int		last;

	if (pids[0] < 2 && size == 1)
		return (0);
	i = -1;
	last = 0;
	while (++i < size)
	{
		aux = waitpid(-1, &status, 0);
		if (aux == -1)
			return (1);
		if (WIFEXITED(status) && aux == pids[size - 1])
			(1 && (last = 1) && (g_msh.err = WEXITSTATUS(status)));
		else if (WIFSIGNALED(status))
		{
			if (!last && WTERMSIG(status) == SIGINT)
				(1 && (g_msh.err = 130) && (last = 1));
			else if (!last && WTERMSIG(status) == SIGQUIT)
				(1 && (g_msh.err = 131) && (last = 1));
		}
	}
	return (0);
}

pid_t	exec_node(t_lstt *node, int idx, int end, int tmp_fd[2])
{
	if (redirect_parser(node->redirect, node->redir_size))
		return (ERR_NODE);
	if (redirect_node(node, tmp_fd))
	{
		g_msh.err = 1;
		return (ERR_GEN);
	}
	if (node->type == STAIR)
		return (exec_fork_stair(node));
	if (expand_args((t_cmd *)node->content, &((t_cmd *)node->content)->args_tk))
		return (ERR_NODE);
	if (idx == 0 && end && is_builtin(((t_cmd *)node->content)->args[0]))
	{
		g_msh.err = exec_builtins(node->content);
		return (0);
	}
	return (exec_fork_cmd(node));
}

int	exec_nodes(t_lstt **node, int size, const int std_fd[2])
{
	t_lstt		*tmp;
	pid_t		*pids;
	int			i;

	pids = ft_calloc(sizeof(pid_t), size);
	if (!node || !*node || !pids)
		return (free(pids), 1);
	(1 && (tmp = *node) && (i = 0));
	(1 && (g_msh.std_fd[0] = dup(IN)) && (g_msh.std_fd[1] = dup(OUT)));
	if (g_msh.std_fd[0] == -1 || g_msh.std_fd[1] == -1)
		return (free(pids), 1);
	while (tmp)
	{
		if (tmp->next && pipe(tmp->fd) == -1)
			return (exec_clean(g_msh.std_fd, std_fd, pids, size));
		pids[i] = exec_node(tmp, i, i == (size - 1), g_msh.std_fd);
		if (pids[i++] == ERR_NODE)
			return (exec_clean(g_msh.std_fd, std_fd, pids, size));
		tmp = tmp->next;
	}
	(pids[0] > 1 && (g_msh.err = 0));
	(((redir_std(g_msh.std_fd, std_fd, 1) || (wait_childs(pids, size))) \
	&& (i = kill_childs(pids, size))) || (i = 0));
	return (free(pids), i);
}

int	executor(t_stair *st)
{
	const int	std_fd[2] = {0, 1};

	if (!st)
		return (0);
	if (st->type != MAIN)
		if (executor(st->step))
			return (1);
	if ((st->type == AND && g_msh.err) || (st->type == OR && !g_msh.err))
		return (0);
	if (exec_nodes(&st->node, st->size, std_fd))
		return (1);
	return (0);
}
