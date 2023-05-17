/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/17 19:10:03 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	syntax_hdoc(char *str, int i)
{
	t_kof	fok;

	init_kof(&fok);
	(1 && (++i) && ft_isspace(str[i]) && (i += 1));
	check_qp(&fok, str[i]);
	if (fok.sq > 0 || fok.dq > 0)
		return (1);
	if (ft_strchr("&|><", str[i]))
		return (1);
	return (0);
}

// 1 && (b = (i++)) && ((str[i] == str[i - 1] && ++i) || 1) && ft_isspace(str[i]) && (i++);
// if (str[b] == '>' && str[i] == '<')
// 	return (1);
// while (str[i] && !((fok.sq < 0 && fok.dq < 0) && ft_isspace(str[i])))
// 	check_qp(&fok, str[i++]);
// (str[i] && ft_isspace(str[i]) && (i++));
// (b - 1 > 0 && ft_isspace(str[b - 1]) && b--);
// if (b - 1 > 0 && str[b - 1] == ')' && ft_strchr("&|><", str[i]))
// 	return (-1);

int	check_rdt(char *str, int i, t_kof *fok)
{
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '>' && ft_strchr("&|><\0", str[i + 2]))
			return (i + 2);
		i++;
	}
	return (i);
}

int	check_redirection(char *str)
{
	t_kof	fok;
	int		i;
	int		b;

	(1 && (i = -1) && init_kof(&fok) && (b = -1));
	while (str[++i])
	{
		check_qp(&fok, str[i]);
		if ((fok.sq < 0 && fok.dq < 0) && (str[i] == '>' || str[i] == '<'))
		{
			i = check_rdt(str, i, &fok);
			if (i = -1)
				return (1);
		}
		if (!str[i])
			break ;
	}
	return (0);
}

int	check_paren(char *str)
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
		(fok.op && (p = check_paren(&str[i + 1])) && (i += p) && (fok.op = 0));
		if (p == -1 || p == 1)
			return (-1);
		if (fok.cp == 1)
		{
			(ft_isspace(str[i + 1]) && (i++));
			if ((str[++i]) && !ft_strchr("&|)><", str[i]))
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
	if (check_paren(str) != (int)ft_strlen(str))
		return (1);
	if (check_redirection(str))
		return (1);
	if (make_blocks(str))
		return (1);
	if (check_blocks(g_msh.block->child))
		return (1);
	if (build_cmd(g_msh.block->child))
		return (1);
	return (0);
}
