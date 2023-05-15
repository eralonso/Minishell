/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:44:19 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/15 18:10:00 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	build_cmd(t_block *block)
{
	if (block->child)
		if (build_cmd(block->child))
			return (1);
	if (block->next)
		if (build_cmd(block->next))
			return (1);
	if (!block->child)
	{
		block->cmd = line_cmd(block->line);
		printf("block->cmd->pre_cmd:%s:\n", block->cmd->pre_cmd);
	}
	return (0);
}

t_cmd	*line_cmd(char	*str)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	char	**cmds;
	int		i;

	(1 && (cmds = split_cmd(str)) && (i = -1) && !(cmd = NULL));
	if (!cmds)
		return (NULL);
	while (cmds[++i])
	{
		tmp = create_cmd(cmds[i]);
		if (!tmp)
			exit (1);
		addback_cmd(&cmd, tmp);
	}
	free(cmds);
	return (cmd);
}

t_cmd	*create_cmd(char *str)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->pre_cmd = str;
	return (new);
}

void	addback_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if (!tmp)
	{
		*cmd = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
