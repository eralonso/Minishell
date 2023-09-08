/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:09:25 by eralonso          #+#    #+#             */
/*   Updated: 2023/09/08 17:09:36 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	strlen_without_spaces(char *str)
{
	int		len;
	int		i;
	int		j;
	int		flag;
	t_kof	fok;

	len = init_kof(&fok) - 1;
	i = 0;
	while (str[i])
	{
		flag = 0;
		j = 0;
		check_qp(&fok, str[i]);
		if (fok.sq < 0 && fok.dq < 0 && str[i] == ' ')
			flag = 1;
		while (flag && str[i + j + 1] == ' ')
			j++;
		i += j;
		if (str[i] && (str[i] != ' ' || (str[i + 1] && i - j != 0)))
			len++;
		if (str[i])
			i++;
	}
	return (len);
}

static void	fill_str_without_spaces(char *str, char *new, int len)
{
	int		j;
	int		i;
	int		flag;
	t_kof	fok;

	i = ft_strlen(str) - 1;
	init_kof(&fok);
	while (i >= 0 && len > 0)
	{
		j = 0;
		flag = 0;
		check_qp(&fok, str[i]);
		if (fok.sq < 0 && fok.dq < 0 && str[i] == ' ')
			flag = 1;
		while (flag && i - j > 0 && str[i - j - 1] == ' ')
			j++;
		i -= j;
		if (i >= 0 && len > 0 && (str[i] != ' ' || str[i + j + 1]))
			new[--len] = str[i];
		if (i >= 0)
			i--;
	}
}

char	*ft_strip(char *str)
{
	char	*new;
	int		len;

	len = strlen_without_spaces(str);
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (NULL);
	fill_str_without_spaces(str, new, len);
	return (new);
}
