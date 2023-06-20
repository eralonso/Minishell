/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/20 13:15:58 by eralonso         ###   ########.fr       */
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

int	start(char *input)
{
	char	*str;
	t_token	*tk;
	t_token	*tk_tmp;
	int		err;

	add_history(input);
	str = validate_input(input, &err);
	if (err >= 0)
		return (err);
	tk = tokenizer(str);
	(ft_free(&input, 2) || ft_free(&str, 2));
	if (!tk)
		return (1);
	tk_tmp = tk;
	g_msh.stair = st_generate(tk);
	tk_clean(&tk_tmp, NEXT);
	if (!g_msh.stair)
		return (1);
	if (!g_msh.ctrl_c && executor(g_msh.stair))
		return (st_clean(&g_msh.stair), 1);
	st_clean(&g_msh.stair);
	ctrl_c(UNSET);
	return (0);
}

char	*validate_input(char *input, int *err)
{
	char	*str;

	*err = -1;
	str = ft_strip(input);
	if (!str)
	{
		*err = 1;
		return (NULL);
	}
	if (ft_isempty(str))
	{
		ft_free(&str, 2);
		*err = 0;
		return (NULL);
	}
	if (check_syntax(str))
	{
		ft_free(&str, 2);
		*err = 1;
		return (NULL);
	}
	return (str);
}
