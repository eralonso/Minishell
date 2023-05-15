/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/15 11:11:02 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	check_qp(t_kof *fok, char c)
{
	((fok->sq < 0) && (c == '\"') && (fok->dq *= -1));
	((fok->dq < 0) && (c == '\'') && (fok->sq *= -1));
	((fok->sq < 0 && fok->dq < 0) && (c == '(') && (fok->op++));
	(((fok->sq < 0 && fok->dq < 0) && c == ')') && (fok->cp++));
	return (1);
}

int	check_brackets(char *str)
{
	int		i;
	int		p;
	t_kof	fok;

	(1 && (i = -1) && init_kof(&fok) && (p = 0));
	while (str[++i])
	{
		
	}
	return (0);
}

int	check_syntax(char *input)
{
	t_kof	fok;
	int		i;

	init_kof(&fok);
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

int	validate_input(char *input)
{
	char	*str;

	if (check_syntax(input))
		return (1);
	str = ft_strip(input);
	if (!str)
		return (1);
	if (check_brackets(str))
		return (1);
	if (make_blocks(str) || g_msh.err)
		return (1);
	if (check_blocks(g_msh.block))
		return (1);
	return (0);
}
