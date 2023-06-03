/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:47:23 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/03 13:37:45 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_cmd	*tk_to_cmd(t_token **tk)
{
	t_cmd	*cmd;
	t_token	*tmp;

	if (!tk || !*tk)
		return (NULL);
	tmp = *tk;
	cmd = NULL;
	return (cmd);
}

t_lstt	*tk_to_lstt(t_token **tk, int type)
{
	t_lstt	*node;

	if (!tk || !*tk)
		return (NULL);
	node = (t_lstt *)ft_calloc(sizeof(t_lstt), 1);
	if (!node)
		return (NULL);
	node->type = type;
	if (type == STAIR)
		node->content = st_generate(tk);
	else
		node->content = tk_to_cmd(tk);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	return (node);
}
