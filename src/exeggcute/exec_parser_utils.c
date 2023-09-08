/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:15:00 by eralonso          #+#    #+#             */
/*   Updated: 2023/09/04 17:29:50 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*retokenize(t_list **first, t_subarg *tmp, char *str)
{
	char	**tokens;
	int		i;

	i = -1;
	tokens = ft_split(tmp->str, ' ');
	if (str != 0)
	{
		ft_lstadd_back(first, ft_lstnew(ft_malloc_strjoin(str, tokens[++i])));
		str = NULL;
	}
	while (tokens[++i + 1] != 0)
		ft_lstadd_back(first, ft_lstnew(ft_strdup(tokens[i])));
	if (tokens[i])
		str = ft_strdup(tokens[i]);
	ft_free(tokens, 1);
	return (str);
}

t_list	*good_expand(t_subarg **sub)
{
	t_list		*first;
	t_subarg	*tmp;
	char		*str;

	first = NULL;
	str = NULL;
	tmp = *sub;
	while (tmp)
	{
		if (!tmp->quote && ft_strchr(tmp->str, ' '))
			str = retokenize(&first, tmp, str);
		else
			str = ft_malloc_strjoin(str, tmp->str);
		tmp = tmp->next;
	}
	ft_lstadd_back(&first, ft_lstnew(str));
	return (first);
}
