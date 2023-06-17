/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwnchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:32:55 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/17 10:36:01 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	*ft_strwnchr(char c, int size)
{
	char	*str;
	int		i;

	i = -1;
	if (size < 0)
		return (NULL);
	str = ft_calloc(sizeof(char), size + 1);
	if (!str)
		return (NULL);
	while (++i < size)
		str[i] = c;
	return (str);
}