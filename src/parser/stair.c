/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stair.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:03:45 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/06 11:57:49 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

// static int	st_go_node(t_token **tmp, t_token *start, 
// t_stair *step, int *type)
// {
// 	t_lstt	*content;

// 	// (tmp && *tmp && (*tmp)->type != PIPE && printf("aaaaa\n"));
// 	*type = tk_cut(tmp);
// 	content = tk_to_lstt(&start);
// 	if (!content)
// 		return (1);
// 	lstt_addback(&step->node, content);
// 	if (start)
// 		tk_clean(&start, NEXT);
// 	return (0);
// }

static int	st_go_node(t_token **tk, t_token **start, t_stair *step, int *type)
{
	t_lstt	*content;

	printf("go node: INIT\n");
	*type = tk_cut(tk);
	printf("go node: start->line == %s\n", (*start)->line);
	content = tk_to_lstt(start);
	if (!content)
		return (1);
	lstt_addback(&step->node, content);
	printf("go node: Pre start clean\n");
	if (*start)
		tk_clean(start, NEXT);
	printf("go node: Post start clean\n");
	// printf("(*tk)->line == %s\n", (*tk)->line);
	*start = *tk;
	printf("go node: EXIT\n");
	return (0);
}

t_stair	*st_generate(t_token *tk)
{
	t_token	*start;
	t_stair	*stair;
	t_stair	*step;
	int		type;
	int		p;

	if (!tk || tk->type == EOCL)
		return (NULL);
	(1 && (step = st_create(NULL, MAIN, 0)) && (start = tk) && (type = -1) \
		&& ((p = 0) || (stair = NULL)));
	if (!step)
		return (NULL);
	while (tk && tk->type != EOCL)
	{
		((tk->type == OP && (p++)) || (tk->type == CP && (p--)));
		((!tk->next || tk->next->type == EOCL) && (tk = tk->next));
		if (!p && (!tk || tk->type == AND || tk->type == OR || tk->type == PIPE))
		{
			if (st_go_node(&tk, &start, step, &type))
			{
				st_clean(&step);
				return (st_clean(&stair));
			}
		}
		if (type == OR || type == AND || type == EOCL)
			st_addfront(&stair, step);
		((type == AND || type == OR) && (step = st_create(NULL, type, 0)));
		if (!step)
			return (st_clean(&stair));
		(tk && (tk = tk->next));
	}
	printf("st_generate: Exit\n");
	return (stair);
}

// t_stair	*st_collect_step(t_token **tk, int *type)
// {
// 	t_stair	*step;
// 	t_kken	*t = tk->nextk;;
// 	t_token	*start;
// 	int		paren;

// 	if (!tk || !*tk)
// 		return (NULL);
// 	step = st_create(NULL, *type, tk_tkcounter(tk, PIPE, LOGIC, ON) + 1);
// 	if (!step)
// 		return (NULL);
// 	(1 && (tmp = *tk) && (start = tmp) && (paren = 0));
// 	while (tmp && tmp->type != EOCL && tmp->type != OR && tmp->type != AND)
// 	{
// 		((tmp->type == OP && (paren++)) || (tmp->type == CP && (paren--))); 
// 		if (tmp->type == PIPE && paren == 0)
// 		{
// 			if (st_go_node(&tmp, start, step, type))
// 				return (st_clean(&step));
// 			start = tmp;
// 		}
// 		(tmp && ((step->final_idx = tmp->idx) || 1) && (tmp = tmp->next));
// 	}
// 	if (st_go_node(&tmp, start, step, type))
// 		return (st_clean(&step));
// 	*tk = tmp;
// 	return (step);
// }

// t_stair	*st_generate(t_token **tk)
// {
// 	t_stair	*stair;
// 	t_token	*tmp;
// 	t_stair	*step;
// 	int		type;

// 	if (!tk || !*tk || (*tk)->type == EOCL)
// 		return (NULL);
// 	(0 || ((tmp = *tk) && 0) || (stair = NULL) || (type = MAIN));
// 	while (tmp && tmp->type != EOCL)
// 	{
// 		step = st_collect_step(&tmp, &type);
// 		if (!step)
// 			return (st_clean(&stair));
// 		st_addfront(&stair, step);
// 	}
// 	return (stair);
// }
