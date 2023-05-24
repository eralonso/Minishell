/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:50:11 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/20 10:51:51 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	print_cmd(t_cmd *cmd, int lvl)
{
	while (cmd)
	{
		printf("lvl %i -> cmd->pre_cmd:%s:\n", lvl, cmd->pre_cmd);
		cmd = cmd->next;
	}
}
