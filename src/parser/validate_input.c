/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/09/28 11:26:51 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	msg_syntax_error(int type, int ret)
{
	char	*str;

	str = NULL;
	((type == RDI || type == RDO || type == RDHD || type == RDAP) \
		&& (str = ft_strdup("newline")));
	(type == OP && (str = ft_strdup("(")));
	(type == CP && (str = ft_strdup(")")));
	(type == PIPE && (str = ft_strdup("|")));
	(type == AND && (str = ft_strdup("&")));
	(type == OR && (str = ft_strdup("||")));
	(type == DQ && (str = ft_strdup("\"")));
	(type == SQ && (str = ft_strdup("\'")));
	(type == ARG && (str = ft_strdup("ARG")));
	if (str)
	{
		ft_printf(2, "Minishell: Syantx error near unexpected token `%s'\n", \
			str);
		free(str);
		g_msh.err = 258;
	}
	return (ret);
}

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
			return (msg_syntax_error(CP, 1));
		if ((fok.sq < 0 && fok.dq < 0) && ((input[i] == '&' \
		&& input[++i] != '&')))
			return (msg_syntax_error(AND, 1));
	}
	if (fok.sq > 0)
		return (msg_syntax_error(SQ, 1));
	if (fok.dq > 0)
		return (msg_syntax_error(DQ, 1));
	if (fok.op > fok.cp)
		return (msg_syntax_error(OP, 1));
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
	ft_free(&str, 2);
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
		*err = 1;
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
