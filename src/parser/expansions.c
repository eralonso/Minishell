/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:24:05 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/09 14:29:02 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

char	*expand_var(char *str)
{
	int		i;
	char	tmp;
	t_env	*node;

	i = var_size(str);
	// printf("expand var: var_size == %i\n", i);
	// printf("expand var: pre str:%s:\n", str);
	tmp = str[i];
	str[i] = '\0';
	// printf("expand var: post str:%s:\n", str);
	node = env_search(&g_msh.env, &str[1]);
	str[i] = tmp;
	if (!node && str[1] != '?')
		return (ft_strdup(""));
	if (str[1] == '?')
		return (ft_itoa(g_msh.err));
	return (ft_strdup(node->value));
}

char	**fill_env_vars(char *str, int size)
{
	char	**vars;
	int		i;
	int		j;
	t_kof	fok;

	i = -1;
	j = 0;
	init_kof(&fok);
	vars = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!vars)
		return (NULL);
	while (str[++i])
	{
		check_qp(&fok, str[i]);
		if (fok.sq < 0 && str[i] == '$' \
		&& (ft_isalnum(str[i + 1]) || ft_strchr("_?", str[i + 1])))
		{
			vars[j] = expand_var(&str[i]);
			// printf("fill env vars: vars[%i]:%s:\n", j, vars[j]);
			if (!vars[j++])
				return (ft_free(vars, 1));
		}
	}
	return (vars);
}

char	*expand_env_var(char *str)
{
	char	*post_env;
	char	**vars;
	int		size;

	size = env_var_count(str);
	if (size == 0)
		return (str);
	vars = fill_env_vars(str, size);
	if (!vars)
		return (NULL);
	post_env = var_line(str, vars, var_total_size(str, vars));
	if (!post_env)
		return (ft_free(vars, 1));
	return (post_env);
}

char	*expand_line(char *str)
{
	char	*new;
	char	*post_env;

	post_env = expand_env_var(str);
	// printf("\n%s\n", post_env);
	if (!post_env)
		return (ft_free(&str, 2));
	new = expand_wildcard(str);
	if (!new)
	{
		ft_free(&str, 2);
		return (ft_free(&post_env, 2));
	}
	printf("expand line: post_env:%s:\n", new);
	return (new);
}

int	expand(t_token **tk)
{
	t_token	*tmp;

	tmp = *tk;
	while (tmp && tmp->type != EOCL)
	{
		if (tmp->type == ARG)
		{
			tmp->line = expand_line(tmp->line);
			if (!tmp->line)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
