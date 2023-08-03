/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:55:00 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 11:35:34 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*ptr;
	void	*tmp;

	if (!lst)
		return (0);
	new_list = 0;
	while (lst)
	{
		tmp = f(lst->content);
		ptr = ft_lstnew(tmp);
		if (!ptr)
		{
			ft_lstclear(&new_list, del);
			del(tmp);
			return (0);
		}
		ft_lstadd_back(&new_list, ptr);
		lst = lst->next;
	}
	return (new_list);
}
