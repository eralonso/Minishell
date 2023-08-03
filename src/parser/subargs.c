/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:58:52 by eralonso          #+#    #+#             */
/*   Updated: 2023/08/03 12:24:41 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	subarg_var(char *str, int *i, char del, t_subarg **args)
{
	t_subarg	*tmp;
	t_subarg	*tmp2;
	t_subarg	**add;

	tmp = ft_calloc(sizeof(t_subarg), 1);
	if (!tmp)
		return (1);
	(1 && (tmp->type = VAR) && (tmp->quote = del));
	(1 && ((*i) += 1) && (add = &tmp) && (tmp->var_in = 0));
	if (!del && (str[*i] == '\'' || str[*i] == '\"'))
		(1 && (del = str[(*i)++]) && (tmp->var_in = 1));
	tmp->expand = extract_subarg(str, i, del, !tmp->var_in);
	if (!tmp->expand)
		return (!subarg_clean(&tmp));
	(tmp->var_in && (add = &tmp->expand));
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
	{
		tmp->n_wilds++;
		(*i)++;
	}
	tmp->str = ft_strwnchr('*', tmp->n_wilds);
	if (!tmp->str)
	{
		free(tmp);
		return (1);
	}
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
	((var && str[start] == '?') && ((*i)++));
	if (del != '\'' && !var && start == *i && str[*i] == '$')
		node = subarg_var_create(str, del, i);
	else
		node = subarg_create(&str[start], *i - start, del);
	(del && del == str[*i] && ((*i)++));
	return (node);
}

t_subarg	*gen_subargs(char *str, char del)
{
	t_subarg	*args;
	t_subarg	*tmp;
	int			i;
	int			err;

	(0 || (i = 0) || (err = 0) || (args = NULL));
	while (str && str[i])
	{
		(!del && (str[i] == '\'' || str[i] == '\"') && (del = str[i]) && (i++));
		if (!del && str[i] == '*')
			err = subarg_wild(str, &i, &args);
		else if (del != '\'' && str[i] == '$')
			err = subarg_var(str, &i, del, &args);
		else
		{
			tmp = extract_subarg(str, &i, del, 0);
			if (!tmp)
				return (subarg_clean(&args));
			subarg_addback(&args, tmp);
		}
		if (err)
			return (subarg_clean(&args));
		(i > 0 && str[i - 1] == del && (del = 0));
	}
	return (args);
}
