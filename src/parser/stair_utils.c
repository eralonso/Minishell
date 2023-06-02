/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stair_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:45:11 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/02 18:49:52 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	st_addfront(t_stair **stair, t_stair *top)
{
	if (!stair)
		return ;
	if (top)
		top->next = *stair;
	*stair = top;
}

t_stair	*st_create()
{
	t_stair	*new;

	new = (t_stair *)ft_calloc(sizeof(t_stair), 1);
	if (!new)
		return (NULL);
	
	return (new);
}