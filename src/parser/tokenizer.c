/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:40:07 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/03 12:55:49 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	catch_args(char *str, int *i)
{
	int		len;
	t_kof	fok;

	(1 && (len = -1) && init_kof(&fok) && ft_isspace(str[*i]) && (*i)++);
	while (str[*i + (++len)])
	{
		check_qp(&fok, str[(*i) + len]);
		if (fok.sq < 0 && fok.dq < 0 && ft_strchr("|&<>() ", str[*i + (len)]))
			break ;
	}
	return (len);
}

t_token	*tk_analyzer(char *str, int *i, int *shlvl, int idx)
{
	t_token	*node;
	int		type;
	int		len;

	type = ARG;
	len = 1;
	(str[(*i)] == '|' && str[(*i) + 1] != '|' && (type = PIPE));
	((str[(*i)] == '|') && (str[(*i) + 1] == '|') && (type = OR));
	((str[(*i)] == '&') && (str[(*i) + 1] == '&') && (type = AND));
	((str[(*i)] == '(') && (type = OP));
	((str[(*i)] == ')') && (type = CP));
	((str[(*i)] == '<') && (str[(*i) + 1] != '<') && (type = RDI));
	((str[(*i)] == '<') && (str[(*i) + 1] == '<') && (type = RDHD));
	((str[(*i)] == '>') && (str[(*i) + 1] != '>') && (type = RDO));
	((str[(*i)] == '>') && (str[(*i) + 1] == '>') && (type = RDAP));
	(type == ARG && (len = catch_args(str, i)));
	(type != ARG && (len += (type % 2)));
	(type == CP && ((*shlvl)--));
	node = tk_create(&str[(*i)], type, len, *shlvl);
	(type == OP && ((*shlvl)++));
	*i += len;
	node->idx = idx;
	return (node);
}

t_token	*tokenizer(char *str)
{
	int		i;
	int		shlvl;
	int		idx;
	t_token	*tk;
	t_token	*node;

	(0 || (i = 0) || (idx = 0) || (shlvl = 0) || (tk = NULL));
	while (str[i] && i != -1)
	{
		node = tk_analyzer(str, &i, &shlvl, idx);
		(str[i] && ft_isspace(str[i]) && i++);
		if (!node)
			return (tk_clean(&tk));
		tk_addback(&tk, node);
		idx++;
	}
	node = tk_create(NULL, EOCL, 0, 0);
	if (!node)
		return (tk_clean(&tk));
	node->idx = idx;
	tk_addback(&tk, node);
	if (check_tokens(&tk))
		return (tk_clean(&tk));
	return (tk);
}
