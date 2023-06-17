/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:56:31 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/17 17:40:37 by eralonso         ###   ########.fr       */
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
	int		last;

	if (pids[0] == 0)
		return (0);
	i = -1;
	last = 0;
	while (++i < size)
	{
		aux = waitpid(-1, &status, 0);
		if (aux == -1)
			return (kill_childs(pids, size));
		if (WIFEXITED(status) && aux == pids[size - 1])
			(1 && (last = 1) && (g_msh.err = WEXITSTATUS(status)));
		else if (WIFSIGNALED(status))
		{
			if (!last && WTERMSIG(status) == SIGINT)
				g_msh.err = 130;
			else if (!last && WTERMSIG(status) == SIGQUIT)
				g_msh.err = 131;
		}
	}
	return (0);
}

pid_t	exec_node(t_lstt *node, int idx, int end)
{
	pid_t	child;

	if (redirect_parser(node->redirect, node->redir_size))
		return (ERR_NODE);
	// redirect_parser(&node);
	// do_redirections(&node);
	// init_signals(N_INTERACT);
	// if (node->type == STAIR)
	// {
	// 	child = fork();
	// 	if (child < 0)
	// 		return (ERR_NODE);
	// 	if (child == 0)
	// 	{
	// 		executor(node->content);
	// 		exit(g_msh.err);
	// 	}
	// 	return (child);
	// }
	// exapand_commands();
	if (idx == 0 && end && is_builtin(((t_cmd *)node->content)->cmd_args[0]))
		return (1);
		// return (exec_builtins(node->content));
	//Si exec node no tiene que hacer fork, devuelve 0.
	// Devuelve ERR_NODE en caso de fallar
	child = fork();
	if (child < 0)
		return (ERR_NODE);
	// if (child == 0)
	// 	exec_cmd(node->content);
	return (child);
}

int	exec_nodes(t_lstt **node, int size)
{
	t_lstt	*tmp;
	pid_t	*pids;
	int		i;
	int		tmp_fd[2];

	if (!node || !*node)
		return (1);
	pids = ft_calloc(sizeof(pid_t), size);
	if (!pids)
		return (1);
	(1 && (tmp = *node) && (i = 0));
	(1 && (tmp_fd[0] = dup(0)) && (tmp_fd[1] = dup(1)));
	while (tmp)
	{
		pids[i] = exec_node(tmp, i, i == (size - 1));
		if (pids[i++] == ERR_NODE)
			return (kill_childs(pids, size), free(pids), 1);
		tmp = tmp->next;
	}
	dup2(tmp_fd[0], 0);
	ft_close(&tmp_fd[0]);
	dup2(tmp_fd[1], 1);
	ft_close(&tmp_fd[1]);
	i = wait_childs(pids, size);
	return (free(pids), i);
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
