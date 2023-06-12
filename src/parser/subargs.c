/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:58:52 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/12 19:20:34 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

// t_subarg	*extract_subarg(char *str, int *i, char def, int var)
// {
// 	t_subarg	*node;
// 	int			quote;
// 	int			start;

// 	((str[*i] == '\'' && (quote = '\'')) \
// 	|| (str[*i] == '\"' && (quote = '\"')) || (quote = def));
// 	(ft_strchr("\'\"", str[*i]) && ((*i)++));
// 	start = *i;
// 	while (str[*i] && str[*i] != quote)
// 	{
// 		if ((!quote && ft_strchr("\'\"", str[*i])) || (quote != '\'' \
// 		&& str[*i] != '$') || (!quote && str[*i] == '*'))
// 			break ;
// 		(str[*i] && ((*i)++));
// 	}
// 	(quote && quote == str[*i] && ((*i)++));
// 	node = subarg_create(&str[start], *i - (start - (quote)), quote, i);
// 	return (node);
// }

int	subarg_var(char *str, int *i, char del, t_subarg **args)
{
	t_subarg	*tmp;
	t_subarg	*tmp2;
	t_subarg	**add;
	int			in;

	tmp = ft_calloc(sizeof(t_subarg), 1);
	if (!tmp)
		return (1);
	(1 && (tmp->type = VAR) && (tmp->quote = del));
	(1 && ((*i) += 1) && (add = &tmp) && (in = 0));
	if (!del && (str[*i] == '\'' || str[*i] == '\"'))
		(1 && (del = str[(*i)++]) && (in = 1));
	tmp->expand = extract_subarg(str, i, del, !in);
	if (!tmp->expand)
		return (!subarg_clean(&tmp));
	(in && (add = &tmp->expand));
	while (del && *i > 0 && str[(*i) - 1] != del)
	{
		tmp2 = extract_subarg(str, i, del, 0);
		if (!tmp2)
			return (!subarg_clean(&tmp));
		subarg_addback(add, tmp2);
	}
	subarg_addback(args, tmp);
	return (0);
}

int	subarg_wild(char *str, int *i, t_subarg **args)
{
	t_subarg	*tmp;

	tmp = ft_calloc(sizeof(t_subarg), 1);
	if (!tmp)
		return (1);
	tmp->type = WILD;
	while (str[*i] == '*')
		(*i)++;
	subarg_addback(args, tmp);
	return (0);
}

t_subarg	*extract_subarg(char *str, int *i, char del, int var)
{
	t_subarg	*node;
	int			start;

	start = *i;
	while (str[*i] && str[*i] != del)
	{
		if ((!del && ft_strchr("\'\"*", str[*i])) || (del != '\'' \
		&& str[*i] == '$') || (var && del != '\'' \
		&& (str[0] == '?' || !ft_strchr(ENV_CHARS, str[*i]))))
			break ;
		(str[*i] && ((*i)++));
	}
	((var && str[0] == '?') && ((*i)++));
	if (del != '\'' && !var && start == *i && str[*i] == '$')
		node = subarg_var_create(str, del, i);
	else
		node = subarg_create(&str[start], *i - start, del);
	(del && del == str[*i] && ((*i)++));
	return (node);
}

t_subarg	*gen_subargs(char *str)
{
	t_subarg	*args;
	t_subarg	*tmp;
	int			i;
	char		del;

	(0 || (i = 0) || (args = NULL) || (del = 0));
	while (str[i])
	{
		(!del && (str[i] == '\'' || str[i] == '\"') && (del = str[i]) && (i++));
		if (del != '\'' && str[i] == '$')
		{
			if (subarg_var(str, &i, del, &args))
				return (subarg_clean(&args));
		}
		else
		{
			tmp = extract_subarg(str, &i, del, 0);
			if (!tmp)
				return (subarg_clean(&args));
			subarg_addback(&args, tmp);
		}
		(i > 0 && str[i - 1] == del && (del = 0));
		if (!del && str[i] == '*' && subarg_wild(str, &i, &args))
			return (subarg_clean(&args));
	}
	print_subargs(&args, 0);
	return (args);
}
