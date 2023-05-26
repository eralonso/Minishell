/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:40:07 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/26 13:32:05 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>



t_token	*tk_analyzer(char *str, int *i, int not_qd, int *shlvl)
{
	t_token	*node;
	int		type;
	int		len;

	type = ARG;
	len = 1;
	(not_qd && str[(*i)] == '|' && str[(*i) + 1] != '|' && (type = PIPE));
	(not_qd && (str[(*i)] == '|') && (str[(*i) + 1] == '|') && (type = OR));
	(not_qd && (str[(*i)] == '&') && (str[(*i) + 1] == '&') && (type = AND));
	(not_qd && (str[(*i)] == '(') && (type = OP));
	(not_qd && (str[(*i)] == ')') && (type = CP));
	(not_qd && (str[(*i)] == '<') && (str[(*i) + 1] != '<') && (type = RDI));
	(not_qd && (str[(*i)] == '<') && (str[(*i) + 1] == '<') && (type = RDHD));
	(not_qd && (str[(*i)] == '>') && (str[(*i) + 1] != '>') && (type = RDO));
	(not_qd && (str[(*i)] == '>') && (str[(*i) + 1] == '>') && (type = RDAP));
	(type == ARG && len = catch_args(str, *i));
	(type != ARG && len += (type % 2));
	node = tk_create(&str[(*i)], type, len, shlvl);
	*i += len;
	return (node);
}

void	tokenizer(t_token *tk, char *str)
{
	int		i;
	int		shlvl;
	t_kof	fok;
	t_token	*node;

	(1 && (i = -1) && init_kof(&fok) && (shlvl = 0));
	while (str[++i] && i != -1)
	{
		check_qp(&fok, str[i]);
		node = tk_analyzer(str, &i, (fok.sq < 0 && fok.dq < 0), &shlvl);
	}
	
}