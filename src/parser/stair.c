/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stair.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:03:45 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 16:43:11 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

static int	st_go_node(t_token **tk, t_token **start, t_stair *step, int *type)
{
	t_lstt	*content;

	*type = EOCL;
	if (tk && *tk)
	{
		*type = (*tk)->type;
		(*tk)->type = EOCL;
	}
	content = tk_to_lstt(start);
	if (!content)
		return (1);
	lstt_addback(&step->node, content);
	*start = NULL;
	if (*tk)
		*start = (*tk)->next;
	return (0);
}

static int	st_fill(t_token **tk, t_token **start, int *type, t_stair **stair)
{
	t_stair	*step;

	if (*type == MAIN || *type == AND || *type == OR)
	{
		step = st_create(NULL, *type, 0);
		if (!step)
			return (1);
		st_addfront(stair, step);
	}
	if (st_go_node(tk, start, *stair, type))
		return (1);
	(*stair)->size++;
	return (0);
}

t_stair	*st_generate(t_token *tk)
{
	t_token	*start;
	t_stair	*stair;
	int		type;
	int		p;

	if (!tk || tk->type == EOCL)
		return (NULL);
	(1 && (start = tk) && (type = MAIN) && ((p = 0) || (stair = NULL)));
	while (tk && tk->type != EOCL)
	{
		((tk->type == OP && (p++)) || (tk->type == CP && (p--)));
		((!tk->next || tk->next->type == EOCL) && (tk = tk->next));
		if (!p && (!tk || tk->type == AND || tk->type == OR \
			|| tk->type == PIPE || tk->type == EOCL))
			if (st_fill(&tk, &start, &type, &stair))
				return (st_clean(&stair));
		(tk && (tk = tk->next));
	}
	return (stair);
}
