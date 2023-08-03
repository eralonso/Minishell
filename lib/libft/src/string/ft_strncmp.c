/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:03:27 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 11:35:40 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (!n || (!s1 && !s2))
		return (0);
	if (!s1 && s2)
		return (*s2);
	if (!s2 && s1)
		return (*s1);
	while (str1[i] && str2[i] && --n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}
