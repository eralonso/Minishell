/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subargs_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:27:18 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/23 18:24:21 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_subarg	*subarg_copy(t_subarg *sub)
{
	t_subarg	*cpy;

	cpy = ft_calloc(sizeof(t_subarg), 1);
	if (!cpy)
		return (NULL);
	cpy->type = sub->type;
	cpy->var_in = sub->var_in;
	cpy->quote = sub->quote;
	if ((cpy->type == TXT || cpy->type == WILD) && sub->str)
	{
		cpy->str = ft_strdup(sub->str);
		if (!cpy->str)
			return (subarg_clean(&cpy));
	}
	else if (cpy->type == VAR)
	{
		cpy->expand = subarg_dup(&sub->expand);
		if (!cpy->expand)
			return (subarg_clean(&cpy));
	}
	return (cpy);
}

t_subarg	*subarg_dup(t_subarg **sub)
{
	t_subarg	*tmp;
	t_subarg	*node;
	t_subarg	*dup;

	if (!sub)
		return (NULL);
	dup = NULL;
	tmp = *sub;
	while (tmp)
	{
		node = subarg_copy(tmp);
		if (!node)
			return (subarg_clean(&dup));
		subarg_addback(&dup, node);
		tmp = tmp->next;
	}
	return (dup);
}
