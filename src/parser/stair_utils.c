/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stair_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:45:11 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 16:43:11 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

void	*st_clean(t_stair **stair)
{
	t_stair	*tmp;
	t_stair	*tmp2;
	t_lstt	*lstt_tmp;

	if (!stair || !*stair)
		return (NULL);
	tmp = *stair;
	while (tmp)
	{
		tmp2 = tmp->step;
		while (tmp->node)
		{
			lstt_tmp = tmp->node->next;
			lstt_clean(&tmp->node);
			tmp->node = lstt_tmp;
		}
		free(tmp);
		tmp = tmp2;
	}
	return (NULL);
}

void	st_addfront(t_stair **stair, t_stair *top)
{
	if (!stair)
		return ;
	if (top)
		top->step = *stair;
	*stair = top;
}

t_stair	*st_create(t_lstt *node, int type, int size)
{
	t_stair	*new;

	new = (t_stair *)ft_calloc(sizeof(t_stair), 1);
	if (!new)
		return (NULL);
	new->type = type;
	new->node = node;
	new->size = size;
	return (new);
}
