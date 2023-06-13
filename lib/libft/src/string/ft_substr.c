/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:20:34 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/13 15:49:06 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if ((len + start) > ft_strlen(s))
		len = ft_strlen(s) - start;
	sub = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, (s + start), len);
	return (sub);
}
