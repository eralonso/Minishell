/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:06:07 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/14 14:37:12 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_block	*create_block(char *str, int size, int lvl, char sep)
{
	t_block	*new;
	int		start;
	int		end;

	end = size;
	new = (t_block *)ft_calloc(sizeof(t_block), 1);
	if (!new)
		return (NULL);
	new->lvl = lvl;
	new->sep = sep;
	while (--end >= 0 && str[end] == ' ')
		size--;
	start = -1;
	while (str[++start] && str[start] == ' ' && start < end)
		size--;
	new->line = ft_substr(str, start, size);
	if (!new->line)
		return (ft_free((char **)&new, 2));
	return (new);
}

t_block	*generate_block(char *str, int lvl)
{
	t_block	*new;
	t_kof	fok;
	int		i;

	if (!str || !*str)
		return (NULL);
	(1 && (i = -1) && ((fok.and = 0) || (fok.or = 0) || (fok.op = 0) || \
		(fok.cp = 0) || ((fok.sq = -1) && (fok.dq = -1))));
	while (str[++i])
	{
		check_qp(&fok, str[i]);
		((fok.sq < 0 && fok.dq < 0) && (fok.op == fok.cp) \
		&& ((str[i] == '&' && (fok.and = 1)) || (ft_strnstr(&str[i], "||", 2) \
		&& (fok.or = 1))));
		if ((fok.cp > fok.op) || (fok.and | fok.or))
			break ;
	}
	(1 && (new = create_block(str, i, lvl, str[i])) && (fok.op && \
		(new->child = generate_block(ft_strchr(str, '(') + 1, lvl + 1))));
	(str[i] && str[i] != ')' && (new->next = generate_block(str + i + 2, lvl)));
	if (!new)
		return (NULL);
	(fok.cp && !str[i] && new->line[ft_strlen(new->line) - 1] != ')' \
		&& !(fok.and | fok.or) && (g_msh.err = lvl));
	return (new);
}

int	make_blocks(char *str)
{
	g_msh.block = create_block(str, -1, 0, 1);
	if (!g_msh.block)
		return (1);
	g_msh.block->child = generate_block(str, 1);
	return (0);
}

int	check_blocks(t_block *block)
{
	if (block->child)
		if (check_blocks(block->child))
			return (1);
	if (block->next)
		if (check_blocks(block->next))
			return (1);
	if (!block->line || !*block->line)
		return (1);
	return (0);
}
