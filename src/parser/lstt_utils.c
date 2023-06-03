/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstt_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:44:41 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/03 13:37:54 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	lstt_addback(t_lstt **list, t_lstt *bottom)
{
	t_lstt	*tmp;

	if (!list)
		return ;
	if (!*list)
	{
		*list = bottom;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = bottom;
}
