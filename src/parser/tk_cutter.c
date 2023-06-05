/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_cutter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:54:39 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/05 15:31:38 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	tk_cut(t_token **tk)
{
	t_token	*tmp;
	t_token	*tmp2;
	int		type;

	if (!tk || !*tk || (*tk)->type == EOCL)
		return (1);
	type = (*tk)->type;
	tmp = (*tk)->next;
	tmp2 = (*tk)->prev;
	free((*tk)->line);	
	free(*tk);
	tmp2->next = NULL;
	*tk = tmp;
	(*tk)->prev = NULL;
	return (type);
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
	if (tmp->type == OP)
		tmp = tmp->next;
	while (tmp && tmp->type != EOCL)
	{
		((tmp->type == OP && (paren++)) || (tmp->type == CP && (paren--)));
		if (tmp->type == CP && !paren)
			break ;
		add = tk_copy(tmp);
		if (!add)
			return (tk_clean(&trimed, NEXT));
		tk_addback(&trimed, add);
		tmp = tmp->next;
	}
	return (trimed);
}
