/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:47:23 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/05 10:48:20 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_cmd	*tk_to_cmd(t_token **tk)
{
	t_cmd	*cmd;

	if (!tk || !*tk)
		return (NULL);
	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->cmd_n = cmd_getcommand(tk);
	if (!cmd->cmd_n)
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd_args = cmd_getargs(tk);
	if (!cmd->cmd_args)
	{
		free(cmd);
		return (ft_free(&cmd->cmd_n, 2));
	}
	return (cmd);
}

t_lstt	*lstt_create(t_token **tk)
{
	t_lstt	*new;

	if (!tk || !*tk)
		return (NULL);
	new = (t_lstt *)ft_calloc(sizeof(t_lstt), 1);
	if (!new)
		return (NULL);
	new->type = CMD;
	if ((*tk)->type == OP)
		new->type = STAIR;
	if (tk_tkcounter(tk, RD, EOCL, ON))
	{
		new->redirect = create_redirect(tk, ON);
		if (!new->redirect)
		{
			free(new);
			return (NULL);
		}
	}
	return (new);
}

t_lstt	*tk_to_lstt(t_token **tk)
{
	t_lstt	*node;
	t_token	*tmp;

	if (!tk || !*tk)
		return (NULL);
	node = lstt_create(tk);
	if (!node)
		return (NULL);
	if (node->type == STAIR)
	{
		tmp = tk_get_in_parenthesis(tk);
		if (!tmp)
			return (ft_free((char **)&node, 2));
		node->content = st_generate(&tmp);
		tk_clean(&tmp);
	}
	else
		node->content = tk_to_cmd(tk);
	if (!node->content)
		return (ft_free((char **)&node, 2));
	return (node);
}
