/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:24:05 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/05 10:28:05 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	areexpansions(char *line)
{
	t_kof	fok;
	int		i;

	if (!line)
		return (0);
	i = -1;
	init_kof(&fok);
	while (line[++i])
	{
		check_qp(&fok, line[i]);
		if (fok.sq < 0 && line[i] == '$')
			return (1);
		if (fok.sq < 0 && fok.dq < 0 && line[i] == '*')
			return (1);
	}
	return (0);
}
