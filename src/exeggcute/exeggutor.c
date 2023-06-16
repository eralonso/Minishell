/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:56:31 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/16 18:12:49 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

// int	exec_nodes(t_lstt **node)
// {
// 	t_lstt	*tmp;
// 	int		last_pid;
// 	int		status;

// 	if (!node || !*node)
// 		return (1);
// 	tmp = *node;
// 	while (tmp)
// 	{
// 		last_pid = ejecuta_node;
// 		check fail
// 		tmp = tmp->next;
// 	}
// 	while (i < n)
// 	{
// 		auxiliar = waitpid(-1, &status, NULL);
// 		if (WIFEXITED(status))
// 		{
// 			if (auxiliar == last_pid)
// 				g_msh.err = WEXITSTATUS(status);
// 		}
// 		else if (WIFSIGNALED(status))
// 		{
			
// 		}
// 	}
// }

int	executor(t_stair *st)
{
	if (!st)
		return (0);
	if (st->type != MAIN)
		if (executor(st->step))
			return (1);
	if ((st->type == AND && g_msh.err) || (st->type == OR && !g_msh.err))
		return (0);
	// if (exec_nodes(&st->node))
	// 	return (1);
	return (0);
}
