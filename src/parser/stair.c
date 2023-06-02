/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stair.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:03:45 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/02 18:44:30 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	tk_cut(t_token **tk)
{
	if (!tk || !*tk || (*tk)->type == EOCL)
		return ;
	(*tk)->prev->next = NULL;
	*tk = (*tk)->next;
}

void	stair_transformer(t_token **tk)
{
	t_token	*tmp;
	t_token	*start;

	tmp = *tk;
	start = tmp;
	while (tmp && tmp->type != EOCL)
	{
		if (tmp->type == PIPE)
		{
			tk_cut(&tmp);
			
			start = tmp;
		}
		else
			tmp = tmp->next;
	}
}