/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:00 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 11:35:33 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	if (*lst)
	{
		while (*lst)
		{
			ptr = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = ptr;
		}
		*lst = 0;
	}
}
