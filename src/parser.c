/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:06:07 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/12 14:21:44 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_block	*create_block(char *str, int size, int lvl, char sep)
{
	t_block	*new;

	new = (t_block *)ft_calloc(sizeof(t_block), 1);
	if (!new)
		return (NULL);
	new->lvl = lvl;
	new->sep = sep;
	new->line = ft_substr(str, 0, size);
	if (!new->line)
		return (ft_free((char **)&new, 2));
	return (new);
}

t_block	*generate_blocks(char *str, int lvl)
{
	t_block	*new;
	t_kof	fok;
	int		i;

	if (!str || !*str)
		return (NULL);
	(1 && (i = -1) && ((fok.op = 0) || (fok.cp = 0) || ((fok.sq = -1) \
		&& (fok.dq = -1))));
	while (str[++i])
	{
		((fok.sq < 0) && (str[i] == '\"') && (fok.dq *= -1));
		((fok.dq < 0) && (str[i] == '\'') && (fok.sq *= -1));
		((fok.sq < 0 && fok.dq < 0) && (str[i] == '(') && (fok.op++));
		(((fok.sq < 0 && fok.dq < 0) && str[i] == ')') && (fok.cp++));
		if ((!fok.op && fok.cp) || ((fok.sq < 0 && fok.dq < 0) && \
		(fok.op == fok.cp) && (str[i] == '&' || ft_strnstr(&str[i], "||", 2))))
			break ;
	}
	(1 && (new = create_block(str, i, lvl, str[i])) && (fok.op && \
		(new->child = generate_blocks(ft_strchr(str, '(') + 1, lvl + 1))));
	(str[i] && str[i] != ')' && (new->next = generate_blocks(str + i + 2, lvl)));
	if (!new)
		return (NULL);
	return (new);
}

int	make_blocks(char *str)
{
	g_msh.block = create_block(str, -1, 0, 1);
	if (!g_msh.block)
		return (1);
	g_msh.block->child = generate_blocks(str, 1);
	return (0);
}
