/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stair.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:03:45 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/05 14:41:17 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

static int	st_go_node(t_token **tmp, t_token *start, t_stair *step, int *type)
{
	t_lstt	*content;

	*type = tk_cut(tmp);
	content = tk_to_lstt(&start);
	if (!content)
		return (1);
	lstt_addback(&step->node, content);
	tk_clean(&start, NEXT);
	return (0);
}

t_stair	*st_collect_step(t_token **tk, int *type)
{
	t_stair	*step;
	t_token	*tmp;
	t_token	*start;
	int		paren;

	if (!tk || !*tk)
		return (NULL);
	step = st_create(NULL, *type, tk_tkcounter(tk, PIPE, LOGIC, ON) + 1);
	if (!step)
		return (NULL);
	(1 && (tmp = *tk) && (start = tmp) && (paren = 0));
	while (tmp && tmp->type != EOCL && tmp->type != OR && tmp->type != AND)
	{
		((tmp->type == OP && (paren++)) || (tmp->type == CP && (paren--)));
		if (tmp->type == PIPE && paren == 0)
		{
			if (st_go_node(&tmp, start, step, type))
				return (st_clean(&step));
			start = tmp;
		}
		(tmp && ((step->final_idx = tmp->idx) || 1) && (tmp = tmp->next));
	}
	if (st_go_node(&tmp, start, step, type))
		return (st_clean(&step));
	*tk = tmp;
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
		step = st_collect_step(&tmp, &type);
		if (!step)
			return (st_clean(&stair));
		st_addfront(&stair, step);
	}
	return (stair);
}
