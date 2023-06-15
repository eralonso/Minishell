/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/15 17:04:37 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

static int	check_syntax(char *input)
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
		if ((fok.sq < 0 && fok.dq < 0) && ((input[i] == '&' \
		&& input[i + 1] != '&') || (input[i] == '|' && input[i + 1] == '&')))
			return (1);
		if ((fok.sq < 0 && fok.dq < 0) && ft_strnstr(&input[i], "&&\0", 2) \
			&& ft_strchr("&|\0", input[++i + 1]))
			return (1);
	}
	if (--i >= 0 && (ft_strchr("&|\\\0", input[i]) \
	|| (fok.sq + fok.dq) != -2 || fok.op != fok.cp))
		return (1);
	return (0);
}

int	validate_input(char *input)
{
	char	*str;
	t_token	*tk;
	t_token	*tk_tmp;

	str = ft_strip(input);
	free(input);
	if (!str)
		return (1);
	if (ft_strlen(str) == 0)
		return (!!ft_free(&str, 2));
	if (check_syntax(str))
		return (!ft_free(&str, 2));
	tk = tokenizer(str);
	if (!tk)
		return (ft_free(&str, 2) == NULL);
	tk_tmp = tk;
	g_msh.stair = st_generate(tk);
	tk_clean(&tk_tmp, NEXT);
	if (!g_msh.stair)
		return (!ft_free(&str, 2));
	free(str);
	return (0);
}
