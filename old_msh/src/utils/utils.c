/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:10:43 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/15 11:29:50 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	init_kof(t_kof *fok)
{
	fok->and = 0;
	fok->or = 0;
	fok->dq = -1;
	fok->sq = -1;
	fok->cp = 0;
	fok->op = 0;
	return (1);
}

char	*ft_strip(char *str)
{
	char	*new;
	t_kof	fok;
	int		i[3];

	((1 && ((i[L] = 0) || (i[F] = 0) || 1)) && (i[I] = -1) && init_kof(&fok));
	while (str[++i[I]])
	{
		check_qp(&fok, str[i[I]]);
		((fok.sq < 0 && fok.dq < 0) && str[i[I]] == ' ' && (i[F] = 1));
		while (i[F] && str[i[I] + 1] && str[i[I] + 1] == ' ')
			i[I]++;
		(!(i[F] = 0) && (i[L]++));
	}
	(new = ft_calloc(sizeof(char), i[L] + init_kof(&fok)));
	if (!new)
		return (NULL);
	while (--i[I] >= 0)
	{
		check_qp(&fok, str[i[I]]);
		((fok.sq < 0 && fok.dq < 0) && str[i[I]] == ' ' && (i[F] = 1));
		while (i[F] && i - 1 >= 0 && str[i[I] - 1] == ' ')
			i[I]--;
		(!(i[F] = 0) && (new[--i[L]] = str[i[I]]));
	}
	return (new);
}
