/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/06 16:29:17 by eralonso         ###   ########.fr       */
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
			(str[i + 1] == str[i] && (i++));
			(ft_isspace(str[i + 1]) && (i++));
			if (!str[i + 1] || ft_strchr("&|><\0", str[i + 1]))
				return (-1);
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
		if ((fok.sq < 0 && fok.dq < 0) && ((input[i] == '&' \
		&& input[i + 1] != '&') || (input[i] == '|' && input[i + 1] == '&')))
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
	t_token	*tk;
	t_token	*tk_tmp;

	str = ft_strip(input);
	if (!str)
		return (1);
	if (ft_strlen(str) == 0)
		return (!!ft_free(&str, 2));
	tk = tokenizer(str);
	if (!tk)
		return (ft_free(&str, 2) == NULL);
	tk_tmp = tk_dup(&tk);
	if (!tk_tmp)
		return (tk_clean(&tk, NEXT) || ft_free(&str, 2) || 1);
	g_msh.stair = st_generate(tk_tmp);
	tk_clean(&tk_tmp, NEXT);
	if (!g_msh.stair)
		return (tk_clean(&tk, NEXT) || ft_free(&str, 2) || 1);
	print_stair(&g_msh.stair, 0);
	free(str);
	return (0);
}
// while (tk_tmp)
// 	(printf("line:%s: && type:%i: && sub_shlvl:%i:\n", 
// 	tk_tmp->line, tk_tmp->type, tk_tmp->sub_shlvl) && (tk_tmp = tk_tmp->next));
