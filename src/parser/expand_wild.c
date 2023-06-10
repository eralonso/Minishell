/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:15:19 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/09 15:35:03 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

static int	are_wildcard(char *str)
{
	t_kof	fok;
	int		i;

	i = 0;
	init_kof(&fok);
	while (str[i])
	{
		check_qp(&fok, str[i]);
		if (fok.sq < 0 && fok.dq < 0 && str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_wildcard(char *str)
{
	char	*expanded;
	char	**to_find;
	char	**survivors;

	if (!are_wildcard(str) || ft_strchr(str, '/'))
		return (str);
	to_find = ft_split_wildcard(str);
	if (!to_find)
		return (NULL);
	return (expanded);
}
