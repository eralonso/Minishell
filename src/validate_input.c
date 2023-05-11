/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/11 13:48:20 by pramos-m         ###   ########.fr       */
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
		(((fok->sq < 0 && fok->dq < 0) && input[i] == ')' && \
			fok->op > fok->cp) && (fok->cp++));
		if ((fok->sq < 0 && fok->dq < 0) && \
			input[i] == '&' && input[i + 1] != '&')
			return (1);
		if ((fok->sq < 0 && fok->dq < 0) && ft_strnstr(&input[i], "&&\0", 2) \
			&& ft_strchr("&|\0", input[++i + 1]))
			return (1);
	}
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
	printf("%s\n", input);
	if (check_syntax(input, &fok))
		return (1);
	// if (check_redirect(input));
	//     return (1);
	return (0);
}
