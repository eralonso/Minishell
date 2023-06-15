/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:56:31 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/15 19:03:02 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	executor(t_stair *st)
{
	if (!st)
		return (0);
	if (st->type != MAIN)
		executor(st->step);
	if ((st->type == AND && g_msh.err) || (st->type == OR && !g_msh.err))
		return (0);
	return (0);
}
