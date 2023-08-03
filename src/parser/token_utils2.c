/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:04:35 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 16:43:11 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	tk_isredirection(t_token *tk)
{
	if (!tk)
		return (0);
	if (tk->type == RDI || tk->type == RDO || tk->type == RDAP)
		return (1);
	if (tk->type == RDHD)
		return (2);
	return (0);
}

t_token	*tk_dup(t_token **tk)
{
	t_token	*tmp;
	t_token	*new;
	t_token	*node;

	if (!tk || !*tk)
		return (NULL);
	tmp = *tk;
	new = NULL;
	while (tmp && tmp->type != EOCL)
	{
		node = tk_copy(tmp);
		if (!node)
			return (tk_clean(&new, NEXT));
		tk_addback(&new, node);
		tmp = tmp->next;
	}
	return (new);
}
