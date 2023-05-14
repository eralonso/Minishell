/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/14 19:24:01 by eralonso         ###   ########.fr       */
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

// int	check_parentesis(char *str)
// {
// 	t_kof	fok;
// 	int		i;
// 	int		cmds;

// 	(1 && ((i = 0) || (cmds = 0) || 1) && (init_kof(&fok)));
// 	while (str[i])
// 	{
// 		check_qp(&fok, str[i]);
// 		if (fok.op > fok.cp)
// 		{
// 			while (str[i] && !((fok.sq < 0 && fok.dq < 0) && str[i] == ')'))
// 			(((check_qp(&fok, str[i]) && ((fok.sq < 0 && fok.dq < 0) \
// 			&& (ft_strchr("&|\0", str[i]) || ft_strnstr(&str[i], "||", 2)) && (cmds++))) \
// 			|| 1) && (i++));
// 			if (cmds <= 1)
// 				return (1);
// 		}
// 		(str[i] && (i++));
// 	}
// 	return (0);
// }

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
	if (make_blocks(str) || g_msh.err)
		return (1);
	if (check_blocks(g_msh.block) && (g_msh.err = -1))
		return (1);
	return (0);
}
