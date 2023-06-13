/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:08:41 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/13 15:45:48 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>
/*
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	start;

	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	i = 0;
	j = 0;
	start = 0;
	while (i < len && haystack[i])
	{
		if (haystack[i] != needle[j])
		{
			i = ++start;
			j = 0;
		}
		if (haystack[i++] == needle[j])
		{
			if (!j++)
				start = i - 1;
			if (!needle[j])
				return ((char *)&haystack[start]);
		}
	}
	return (0);
}
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*tmp;
	int		len_hay;

	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	tmp = (char *)haystack;
	len_hay = ft_strlen(haystack);
	while (tmp && *tmp && len_hay - ft_strlen(tmp) <= len)
	{
		i = 0;
		tmp = ft_strchr(tmp, needle[0]);
		while (tmp && tmp[i] && needle[i] && tmp[i] == needle[i])
			i++;
		if (!needle[i] && len_hay + i - ft_strlen(tmp) <= len)
			return (tmp);
		if (tmp && *tmp)
			tmp++;
	}
	return (NULL);
}
