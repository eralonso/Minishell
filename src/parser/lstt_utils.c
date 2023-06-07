/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstt_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:44:41 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/07 18:27:41 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	*lstt_clean(t_lstt **lst)
{
	if (!lst || !*lst)
		return (NULL);
	rd_clean((*lst)->redirect, (*lst)->redir_size);
	free((*lst));
	return (NULL);
}

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
