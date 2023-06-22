/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:48:24 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/22 18:25:53 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	exec_fork_stair(t_lstt *node, int tmp_fd[2])
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (ERR_NODE);
	if (child == 0)
	{
		ft_close(&node->fd[0]);
		if (redirect_node(node, tmp_fd))
			exit(ERR_GEN);
		executor(node->content);
		exit(g_msh.err);
	}
	if (node->next)
	{
		dup2(node->fd[0], 0);
		ft_close(&node->fd[0]);
		dup2(node->fd[1], 1);
		ft_close(&node->fd[1]);
	}
	return (child);
}

int	exec_fork_cmd(t_lstt *node, int tmp_fd[2])
{
	pid_t	child;

	init_signals(N_INTERACT);
	child = fork();
	if (child < 0)
		return (ERR_NODE);
	if (child == 0)
	{
		ctrl_c(SET);
		ft_close(&node->fd[0]);
		if (redirect_node(node, tmp_fd))
			exit(ERR_GEN);
		if (((t_cmd *)node->content)->args[0])
			exec_cmd((t_cmd *)node->content);
		exit(0);
	}
	if (node->next)
	{
		dup2(node->fd[0], 0);
		ft_close(&node->fd[0]);
		dup2(node->fd[1], 1);
		ft_close(&node->fd[1]);
	}
	return (child);
}
