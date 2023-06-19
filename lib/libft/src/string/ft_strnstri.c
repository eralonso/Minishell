/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:04:57 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/19 14:20:15 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

int	ft_strnstri(char *haystack, char *needle, size_t len)
{
	size_t	i;
	char	*tmp;
	int		len_hay;

	if (!haystack || !needle)
		return (-1);
	if (!*needle)
		return (0);
	tmp = haystack;
	len_hay = ft_strlen(haystack);
	while (tmp && *tmp && len_hay - ft_strlen(tmp) <= len)
	{
		i = 0;
		tmp = ft_strchr(tmp, needle[0]);
		while (tmp && tmp[i] && needle[i] && tmp[i] == needle[i])
			i++;
		if (!needle[i] && len_hay + i - ft_strlen(tmp) <= len)
			return (tmp - haystack);
		if (tmp && *tmp)
			tmp++;
	}
	return (-1);
}
