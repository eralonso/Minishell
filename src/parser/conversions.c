/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:47:23 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/06 17:47:19 by eralonso         ###   ########.fr       */
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
		ft_free(&cmd->cmd_n, 2);
		free(cmd);
		return (NULL);
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
	new->redir_size = tk_tkcounter(tk, RD, EOCL, ON);
	if (new->redir_size)
	{
		new->redirect = create_redirect(tk, new->redir_size, ON);
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
	t_token	*tmp2;

	if (!tk || !*tk)
		return (NULL);
	node = lstt_create(tk);
	if (!node)
		return (NULL);
	if (node->type == STAIR)
	{
		tmp = tk_get_in_parenthesis(tk);
		if (!tmp)
			return (lstt_clean(&node));
		tmp2 = tmp;
		node->content = st_generate(tmp);
		tk_clean(&tmp2, NEXT);
	}
	else
		node->content = tk_to_cmd(tk);
	if (!node->content)
		return (ft_free((char **)&node, 2));
	return (node);
}
