/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/12 14:21:09 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	check_syntax(char *input, t_kof *fok)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		((fok->sq < 0) && (input[i] == '\"') && (fok->dq *= -1));
		((fok->dq < 0) && (input[i] == '\'') && (fok->sq *= -1));
		((fok->sq < 0 && fok->dq < 0) && (input[i] == '(') && (fok->op++));
		(((fok->sq < 0 && fok->dq < 0) && input[i] == ')') && (fok->cp++));
		if (fok->cp > fok->op)
			return (1);
		if ((fok->sq < 0 && fok->dq < 0) && \
			input[i] == '&' && input[i + 1] != '&')
			return (1);
		if ((fok->sq < 0 && fok->dq < 0) && ft_strnstr(&input[i], "&&\0", 2) \
			&& ft_strchr("&|\0", input[++i + 1]))
			return (1);
	}
	while (i && input[--i] == ' ')
		;
	if (i && (ft_strchr("&|\\\0", input[i]) || (fok->sq + fok->dq) != -2 \
		|| fok->op != fok->cp))
		return (1);
	return (0);
}

int	validate_input(char *input)
{
	t_kof	fok;

	fok.dq = -1;
	fok.sq = -1;
	fok.op = 0;
	fok.cp = 0;
	fok.and = 0;
	fok.or = 0;
	if (check_syntax(input, &fok))
		return (1);
	if (make_blocks(input))
		return (1);
	return (0);
}
