/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:35:23 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/09 16:07:26 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	size_to_find(char *str)
{
	int		i;
	int		size;
	t_kof	fok;

	init_kof(&fok);
	i = 0;
	size = 0;
	while (str[i])
	{
		check_qp(&fok, str[i]);
		while (str[i] && fok.sq < 0 && fok.dq < 0 && str[i] == '*')
		{
			check_qp(&fok, str[i]);
			i++:
		}
		if (str[i] && !(str[i] == '\'' && str[i + 1] == '\'') \
			&& !(str[i] == '\"' && str[i + 1] == '\"'))
			size++;
		while (str[i] && !(fok.sq < 0 && fok.dq < 0 && str[i] == '*'))
		{
			check_qp(&fok, str[i]);
			i++:
		}
	}	
	return (size);
}

char	**ft_split_wildcard(char *str)
{
	char	**to_find;
	int		i;
	int		size;
	
	i = 0;
	size = size_to_find(str);
	to_find = ft_calloc(sizeof(char *), size + 1);
	if (!to_find)
		return (NULL);
	
	return (to_find);
}