/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:35 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/15 17:46:31 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

static int	arg_num(char *str);

char	**split_cmd(char *str)
{
	int		i;
	int		j;
	int		start;
	char	**res;
	t_kof	fok;

	res = ft_calloc(sizeof(char *), arg_num(str));
	j = 0;
	i = -1;
	while (str[++i])
	{
		start = i;
		while (str[i] && (fok.sq < 0 && fok.dq < 0) && str[i] == '|')
			i++;
		res[j] = ft_substr(str, start, i);
		if (!res[j])
			return (ft_free(res, 1));
		if (!str[i])
			break ;
	}
	return (res);
}

static int	arg_num(char *str)
{
	int		i;
	int		cntr;
	t_kof	fok;

	((init_kof(&fok) || 1) && (i = -1) && (cntr = 1));
	while (str[++i])
	{
		check_qp(&fok, str[i]);
		if ((fok.sq < 0 && fok.dq < 0) && str[i] == '|')
			cntr++;
	}
	return (cntr);
}
