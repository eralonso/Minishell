/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:35 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/20 10:48:48 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

static int	arg_num(char *str);

char	**split_cmd(char *str)
{
	int		i;
	int		j;
	int		s;
	char	**res;
	t_kof	fok;

	res = ft_calloc(sizeof(char *), arg_num(str) + 1);
	j = 0;
	i = -1;
	init_kof(&fok);
	while (str[++i])
	{
		((check_qp(&fok, str[i])) && (s = i));
		while (str[i] && (fok.sq < 0 && fok.dq < 0 && fok.op >= fok.cp) \
		&& (str[i] != '|' || (str[i] == '|' || str[i + 1] == '|')))
			check_qp(&fok, str[i++]);
		res[j] = ft_substr(str, s, (i - s) - ft_isspace(str[i - (i > 0)]));
		if (!res[j++])
			return (ft_free(res, 1));
		if (!str[i])
			break ;
	}
	return (res);
}
		// printf("c: %c && i: %i\n", str[i], i);

static int	arg_num(char *str)
{
	int		i;
	int		cntr;
	t_kof	fok;

	((init_kof(&fok) || 1) && (i = -1) && (cntr = 1));
	while (str[++i])
	{
		check_qp(&fok, str[i]);
		if ((fok.sq < 0 && fok.dq < 0 && fok.op == fok.cp) && str[i] == '|' \
			&& str[i + 1] != '|')
			cntr++;
	}
	printf("str:%s:#--# cntr: %i\n", str, cntr);
	return (cntr);
}
