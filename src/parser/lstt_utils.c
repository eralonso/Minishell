/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstt_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:44:41 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/20 12:43:10 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	*lstt_clean(t_lstt **lst)
{
	t_lstt	*tmp;

	if (!lst || !*lst)
		return (NULL);
	tmp = *lst;
	rd_clean(tmp->redirect, tmp->redir_size);
	if (tmp->fd[0] > 1)
		ft_close(&tmp->fd[0]);
	if (tmp->fd[1] > 1)
		ft_close(&tmp->fd[1]);
	if (tmp->type == STAIR)
		st_clean((t_stair **)&tmp->content);
	else
		cmd_clean((t_cmd **)&tmp->content);
	free(tmp);
	*lst = NULL;
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
	bottom->prev = tmp;
}
