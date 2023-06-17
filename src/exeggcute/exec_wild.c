/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wild.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:27:56 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/17 19:03:59 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	arewildcard(t_subarg **sub)
{
	t_subarg	*tmp;

	if (!sub || !*sub)
		return (0);
	tmp = *sub;
	while (tmp)
	{
		if (tmp->type == WILD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	expand_wilds(t_token *tk)
{
	return (tk == NULL);
}
