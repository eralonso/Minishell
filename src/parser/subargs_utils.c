/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subargs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:11:12 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/10 18:43:25 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_subarg	*subarg_envar(char *str, char p_quote)
{
	int			i;
	int			quote;
	t_subarg	*node;

	i = 0;
	((*str == '\'' && (quote = '\'')) || ((*str == '\"' && (quote = '\"'))) \
	|| (quote = p_quote));
	while (str[i])
	{
		if (str[i])
		i++;
	}
	return (node);
}

void	*subarg_clean(t_subarg **sub)
{
	t_subarg	*tmp;
	t_subarg	*tmp2;

	if (!sub || !*sub)
		return (NULL);
	tmp = *sub;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->expand)
			subarg_clean(&tmp->expand);
		if (tmp->str)
			free(tmp->str);
		free(tmp);
		tmp = tmp2;
	}
	return (NULL);
}

void	subarg_addback(t_subarg **args, t_subarg *bottom)
{
	t_subarg	*tmp;

	if (!args)
		return ;
	if (!*args)
	{
		*args = bottom;
		return ;
	}
	tmp = *args;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = bottom;
}

t_subarg	*subarg_create(char *str, int size, char quote, char *type)
{
	t_subarg	*new;

	new = ft_calloc(sizeof(t_subarg), 1);
	if (!new)
		return (NULL);
	new->quote = quote;
	((*type == '$' && (new->type = VAR)) \
		|| (*type == '*' && (new->type = VAR)) || (new->type = TXT));
	if (*type != '$' && *type != '*')
	{
		new->str = ft_substr(str, 0, size);
		if (!new->str)
			free(new);
		if (!new->str)
			return (NULL);
	}
	else if (*type == '$')
	{
		new->expand = subarg_envar(type);
		if (!new->expand)
			return (subarg_clean(&new));
		if (quote)
		{
		}
	}
	return (new);
}
