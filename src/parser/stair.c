/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stair.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:03:45 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/03 17:37:21 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_stair	*st_collect_step(t_token **tk, int type)
{
	t_stair	*step;
	t_token	*tmp;
	t_token	*start;
	t_lstt	*content;
	int		paren;

	if (!tk || !*tk)
		return (NULL);
	step = st_create(NULL, type, tk_tkcounter(tk, PIPE, LOGIC, ON) + 1);
	if (!step)
		return (NULL);
	(1 && (tmp = *tk) && (start = tmp) && (paren = 0));
	while (tmp && tmp->type != EOCL)
	{
		((tmp->type == OP && (paren++)) || (tmp->type == CP && (paren--)));
		if (tmp->type == PIPE && paren == 0)
		{
			tk_cut(&tmp);
			(1 && (content = tk_to_lstt(&start)) && (start = tmp));
			if (!content)
				return (st_clean(&step));
			lstt_addback(&step->node, content);
		}
		(tmp && ((step->final_idx = tmp->idx) || 1) && (tmp = tmp->next));
	}
	return (step);
}

t_stair	*st_generate(t_token **tk)
{
	t_stair	*stair;
	t_token	*tmp;
	t_stair	*step;
	int		type;

	if (!tk || !*tk || (*tk)->type == EOCL)
		return (NULL);
	(0 || ((tmp = *tk) && 0) || (stair = NULL) || (type = MAIN));
	while (tmp && tmp->type != EOCL)
	{
		step = st_collect_step(&tmp, type);
		if (!step)
			return (st_clean(&stair));
		st_addfront(&stair, step);
		while (tmp && tmp->type != EOCL && tmp->idx != step->final_idx)
			tmp = tmp->next;
		(tmp && tmp->type != EOCL && tmp->type != AND && tmp->type != OR \
			&& (tmp = tmp->next));
		(tmp && (type = tmp->type) && (tmp = tmp->next));
	}
	return (stair);
}
