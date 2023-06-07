/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:24:05 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/07 19:12:19 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

char	*expand_env_var(char *str)
{
	char	*post_env;

	post_env = str;
	return (post_env);
}

char	*expand_line(char *str, int f_pipe)
{
	char	*new;
	char	*post_env;

	post_env = expand_env_var(str);
	if (!post_env)
		return (NULL);
	if (f_pipe)
		return (NULL);
	new = NULL;
	return (new);
}

int	wdc_able(char *str)
{
	if (str)
		return (1);
	return (0);
}

int	are_expansions(char *line)
{
	t_kof	fok;
	int		i;

	if (!line)
		return (0);
	i = -1;
	init_kof(&fok);
	while (line[++i])
	{
		check_qp(&fok, line[i]);
		if (fok.sq < 0 && line[i] == '$')
			return (1);
		if (fok.sq < 0 && fok.dq < 0 && line[i] == '*' \
		&& !ft_strchr(line, '/') && wdc_able(line))
			return (1);
	}
	return (0);
}

int	expand(t_token **tk)
{
	int		f_pipe;
	t_token	*tmp;
	int		paren;

	(0 || ((tmp = *tk) && 0) || (f_pipe = 0) || (paren = 0));
	while (tmp && tmp->type != EOCL)
	{
		if (tmp->type == ARG && are_expansions(tmp->line))
		{
			tmp->line = expand_line(tmp->line, f_pipe);
			if (!tmp->line)
				return (1);
		}
		((tmp->type == OP && (paren++)) || (tmp->type == CP && (paren--)));
		if (!paren && tmp->type == PIPE)
			f_pipe = 1;
		tmp = tmp->next;
	}
	return (0);
}
