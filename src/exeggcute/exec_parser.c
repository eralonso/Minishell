/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:39:37 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/20 11:20:18 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

char	*subarg_join(t_subarg **sub)
{
	t_subarg	*tmp;
	char		*str;

	if (!sub || !*sub)
		return (NULL);
	str = NULL;
	tmp = *sub;
	while (tmp)
	{
		str = ft_malloc_strjoin(str, tmp->str);
		if (!str)
			return (NULL);
		tmp = tmp->next;
	}
	return (str);
}

char	*expand_dollar(t_subarg *expand, int var_in)
{
	t_env	*tmp;

	if (var_in && expand)
	{
		if (expand_vars(&expand))
			return (NULL);
		return (subarg_join(&expand));
	}
	else if (!var_in)
	{
		if (!expand->str)
			return (ft_strdup("$\0"));
		tmp = env_search(&g_msh.env, expand->str);
		if (!tmp && !ft_strncmp(expand->str, "?\0", 2))
			return (ft_itoa(g_msh.err));
		if (tmp)
			return (ft_strdup(tmp->value));
	}
	return (ft_strdup(""));
}

int	expand_vars(t_subarg **args)
{
	t_subarg	*tmp;

	if (!args || !*args)
		return (1);
	tmp = *args;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			tmp->str = expand_dollar(tmp->expand, tmp->var_in);
			if (!tmp->str)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*subarg_expand(t_token *tk)
{
	char	*str;
	int		err;

	err = 0;
	if (expand_vars(&tk->args))
		return (NULL);
	if (arewildcard(&tk->args))
	{
		str = expand_wilds(&tk->args, &err);
		if (err)
			return (NULL);
		if (str)
			return (str);
	}
	str = subarg_join(&tk->args);
	return (str);
}
