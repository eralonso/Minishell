/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:58:52 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/10 16:19:26 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_subarg	*extract_subarg(char *str, int *i, char def)
{
	t_subarg	*node;
	int			quote;
	int			start;

	((str[*i] == '\'' && (quote = '\'')) \
	|| (str[*i] == '\"' && (quote = '\"')) || (quote = def));
	(ft_strchr("\'\"", str[*i]) && ((*i)++));
	start = *i;
	while (str[*i] && str[*i] != quote)
	{
		if ((!quote && ft_strchr("\'\"", str[*i])) || (quote != '\'' \
		&& str[*i] != '$') || (!quote && str[*i] == '*'))
			break ;
		(str[*i] && ((*i)++));
	}
	(quote && quote == str[*i] && ((*i)++));
	node = subarg_create(&str[start], *i - (start - (quote)), quote, &str[*i]);
	return (node);
}

t_subarg	*gen_subargs(char *str)
{
	t_subarg	*args;
	t_subarg	*tmp;
	int			i;

	i = 0;
	args = NULL;
	while (str[i])
	{
		tmp = extract_subarg(str, &i, 0);
		if (!tmp)
			return (subarg_clean(&args));
		subarg_addback(&args, tmp);
	}
	return (args);
}
