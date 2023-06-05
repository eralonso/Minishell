/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_cutter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:54:39 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/05 10:31:15 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	tk_cut(t_token **tk)
{
	if (!tk || !*tk || (*tk)->type == EOCL)
		return (1);
	if ((*tk)->prev)
		(*tk)->prev->next = NULL;
	*tk = (*tk)->next;
	(*tk)->prev = NULL;
	return (1);
}

t_token	*tk_get_in_parenthesis(t_token **tk)
{
	t_token	*trimed;
	t_token	*tmp;
	t_token	*add;
	int		paren;

	if (!tk || !*tk)
		return (NULL);
	(1 && (tmp = *tk) && (paren = 1) && (trimed = NULL));
	while (tmp && tmp->type != EOCL)
	{
		((tmp->type == OP && (paren++)) || (tmp->type == CP && (paren--)));
		if (tmp->type == CP && !paren)
			break ;
		add = tk_copy(tmp);
		if (!add)
			return (tk_clean(&trimed));
		tk_addback(&trimed, add);
		tmp = tmp->next;
	}
	return (trimed);
}
