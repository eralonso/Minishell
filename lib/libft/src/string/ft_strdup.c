/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:16:49 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/19 18:39:16 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	i;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dup = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < len)
		dup[i] = str[i];
	return (dup);
}
