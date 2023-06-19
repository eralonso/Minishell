/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wild.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:27:56 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/19 12:56:46 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	arewildcard(t_subarg **sub)
{
	t_subarg	*tmp;

	if (!sub || !*sub)
		return (0);
	tmp = *sub;
	while (tmp)
	{
		if (tmp->type == WILD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*join_wild(t_subarg *tmp)
{
	char	*str;

	str = NULL;
	while (tmp && tmp->type != WILD)
	{
		str = ft_malloc_strjoin(str, tmp->str);
		if (!str)
			return (NULL);
		tmp = tmp->next;
	}
	return (str);
}

int	expand_wilds(t_token *tk, t_subarg **args)
{
	t_subarg	*tmp;
	char		**wilds;
	char		*str;
	int			idx;
	int			first;

	wilds = get_wildcard(CURRENT_DIR);
	if (!wilds)
		return (1);
	(1 && (tmp = *args)) && ((first = 1));
	(0 || (idx = 0) || (str = NULL));
	while (tmp)
	{
		if (tmp->type != WILD)
		{
			str = join_wild(tmp);
			if (!str)
				return (ft_free(wilds, 1), 1);
		}
		if (str && first)
		{
			tmp = tmp->next;
		}
		else if (str && tmp->type == WILD)
		{

		}
		else if (str)
		{
			
		}
		first = 0;
	}
	return (0);
}
