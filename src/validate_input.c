/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/15 17:04:48 by pramos-m         ###   ########.fr       */
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

int	check_bb(char *str, int i)
{
	if (i > 0)
	{
		(ft_isspace(str[i - 1]) && (i--));
		if (i - 1 >= 0 && !ft_strchr("&|(", str[i - 1]))
			return (1);
	}
	return (0);
}

int	check_brackets(char *str)
{
	int		i;
	int		p;
	t_kof	fok;

	(1 && (i = -1) && init_kof(&fok) && (p = 0));
	while (str[++i])
	{
		check_qp(&fok, str[i]);
		if ((fok.sq < 0 && fok.dq < 0) && (str[i] == '(') && check_bb(str, i))
			return (-1);
		(fok.op && (p = check_brackets(&str[i + 1])) && (i += p));
		if (p == -1 || p == 1)
			return (-1);
		if (fok.cp == 1)
		{
			(ft_isspace(str[i + 1]) && (i++));
			if ((str[i + 1]) && !ft_strchr("&|)", str[i + 1]))
				return (-1);
			else
				return (i + 1);
		}
		if (!str[i])
			break ;
	}
	return (i);
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
	if (check_brackets(str) != (int)ft_strlen(str))
		return (1);
	if (make_blocks(str) || g_msh.err)
		return (1);
	if (check_blocks(g_msh.block->child))
		return (1);
	if (build_cmd(g_msh.block->child))
		return (1);
	return (0);
}
