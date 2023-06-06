/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_cutter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:54:39 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/06 13:59:49 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	tk_cut(t_token **tk)
{
	t_token	*tmp;
	t_token	*tmp2;
	int		type;

	if (!tk || !*tk)
		return (EOCL);
	tmp = NULL;
	tmp2 = NULL;
	printf("(*tk)->line == %s\n", (*tk)->line);
	// printf("(*tk)->prev->line == %s\n", (*tk)->prev->line);
	// printf("(*tk)->next->line == %s\n", (*tk)->next->line);
	type = (*tk)->type;
	if ((*tk)->next)
		tmp = (*tk)->next;
	if ((*tk)->prev)
		tmp2 = (*tk)->prev;
	free((*tk)->line);
	free(*tk);
	if (tmp)
		tmp->prev = NULL;
	if (tmp2)
		tmp2->next = NULL;
	*tk = tmp;
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
	add = tk_create(NULL, EOCL, 0, 0);
	if (!add)
		return (tk_clean(&trimed, NEXT));
	tk_addback(&trimed, add);
	return (trimed);
}
