/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/14 16:25:41 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	check_qp(t_kof *fok, char c)
{
	((fok->sq < 0) && (c == '\"') && (fok->dq *= -1));
	((fok->dq < 0) && (c == '\'') && (fok->sq *= -1));
	((fok->sq < 0 && fok->dq < 0) && (c == '(') && (fok->op++));
	(((fok->sq < 0 && fok->dq < 0) && c == ')') && (fok->cp++));
}

int	check_syntax(char *input)
{
	t_kof	fok;
	int		i;

	(1 && ((fok.and = 0) || (fok.or = 0) || (fok.op = 0) || \
		(fok.cp = 0) || ((fok.sq = -1) && (fok.dq = -1))));
	i = -1;
	while (input[++i])
	{
		check_qp(&fok, input[i]);
		if (fok.cp > fok.op)
			return (1);
		if ((fok.sq < 0 && fok.dq < 0) && \
			input[i] == '&' && input[i + 1] != '&')
			return (1);
		if ((fok.sq < 0 && fok.dq < 0) && ft_strnstr(&input[i], "&&\0", 2) \
			&& ft_strchr("&|\0", input[++i + 1]))
			return (1);
	}
	while (i && input[--i] == ' ')
		;
	if (i && (ft_strchr("&|\\\0", input[i]) || (fok.sq + fok.dq) != -2 \
		|| fok.op != fok.cp))
		return (1);
	return (0);
}

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
		((fok.sq < 0 && fok.dq < 0) && str[i[I]++] == ' ' && (i[F] = 1));
		while (i[F] && str[i[I] + 1] && str[i[I] + 1] == ' ')
			i[I]++;
		(((i[F] = 0) || 1) && (i[L]++));
	}
	((new = ft_calloc(sizeof(char), i[L] + 1)) && (init_kof(&fok)));
	if (!new)
		return (NULL);
	while (--i[I] >= 0)
	{
		check_qp(&fok, str[i[I]]);
		((fok.sq < 0 && fok.dq < 0) && str[i[I]] == ' ' && (i[F] = 1) && (new[--i[L]] = ' '));
		while (i[F] && i - 1 >= 0 && str[i[I]] == ' ')
			i[I]--;
		(((i[F] = 0) || 1) && i[L] > 0 && (new[--i[L]] = str[i[I]]));
	}
	return (new);
}

int	validate_input(char *input)
{
	char	*str;
	
	if (check_syntax(input))
		return (1);
	str = ft_strip(input);
	if (!str)
		return (1);
	if (make_blocks(input) || g_msh.err)
		return (1);
	if (check_blocks(g_msh.block))
		return (1);
	return (0);
}
