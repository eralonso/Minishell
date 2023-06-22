/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wild.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:27:56 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/22 18:19:29 by eralonso         ###   ########.fr       */
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

char	*join_wild(t_subarg **sub)
{
	char		*str;
	t_subarg	*tmp;

	if (!sub)
		return (NULL);
	str = NULL;
	tmp = *sub;
	while (tmp && tmp->type != WILD)
	{
		str = ft_malloc_strjoin(str, tmp->str);
		if (!str)
			return (NULL);
		tmp = tmp->next;
	}
	*sub = tmp;
	return (str);
}

int	init_wild(t_wild **wild)
{
	*wild = ft_calloc(sizeof(t_wild), 1);
	if (!*wild)
		return (1);
	(*wild)->wilds = get_wildcard(CURRENT_DIR);
	if (!(*wild)->wilds)
		return (1);
	(*wild)->size = ft_matrixlen((*wild)->wilds);
	(*wild)->rem = (*wild)->size;
	(*wild)->idxs = ft_calloc(sizeof(int), (*wild)->size);
	if (!(*wild)->idxs)
		return (ft_free((*wild)->wilds, 1), 1);
	return (0);
}

void	select_wilds(t_wild *wild, char *str, int first, int last)
{
	int	i;
	int	size;
	int	res;
	int	(*cmp)(char *, char *, size_t);

	i = -1;
	(((first || last) && (size = ft_strlen(str))) || (size = 0xFFFFFF));
	cmp = ft_strnstri;
	((first && (cmp = ft_strncmp)) || (last && (cmp = ft_strrncmp)));
	while (++i < wild->size)
	{
		if (wild->wilds[i])
		{
			res = cmp(&wild->wilds[i][wild->idxs[i]], str, size);
			if (((first || last) && res) || (!first && !last && res == -1))
				(ft_free(&wild->wilds[i], 2) || (wild->rem--));
			else if (last || first)
				wild->idxs[i] += size;
			else
				wild->idxs[i] += res + ft_strlen(str);
		}
	}
}

t_wild	*expand_wilds(t_subarg **args)
{
	t_subarg	*tmp;
	t_wild		*wild;
	char		*str;
	int			first;

	if (init_wild(&wild))
		return (NULL);
	(1 && (tmp = *args)) && ((first = 1) && ((str = NULL)));
	while (tmp)
	{
		if (tmp->type != WILD)
		{
			str = join_wild(&tmp);
			if (!str)
				return (free(wild->idxs), ft_free(wild->wilds, 1));
			select_wilds(wild, str, first, !(tmp && tmp->type == WILD));
		}
		((ft_free(&str, 2) || 1) && tmp && (tmp = tmp->next) && (first = 0));
	}
	free(wild->idxs);
	return (wild);
}
	// (wild->rem && (line = ft_matrixjoin_size(wild->wilds, ' ', wild->size)));
	// (wild->rem && !line && (*err = 1));
	// ft_free_size(wild->wilds, wild->size);
