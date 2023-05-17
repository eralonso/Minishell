/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:44:19 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/17 18:13:45 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	print_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		printf("cmd->pre_cmd:%s:\n", cmd->pre_cmd);
		cmd = cmd->next;
	}
}

int	build_cmd(t_block *block)
{

	block->cmd = line_cmd(block->line);
	if (!block->cmd)
		return (1);
	print_cmd(block->cmd);
	if (block->child)
		if (build_cmd(block->child))
			return (1);
	if (block->next)
		if (build_cmd(block->next))
			return (1);
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
			return (ft_free(cmds, cmd_lstclear(&cmd, 1)));
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

int	cmd_lstclear(t_cmd **cmd, int ret)
{
	t_cmd	*tmp;
	t_cmd	*top;

	(cmd && (tmp = *cmd)) || (tmp = NULL);
	while (tmp)
	{
		top = tmp->next;
		free(tmp);
		tmp = top;
	}
	return (ret);
}
