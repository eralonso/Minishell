/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 09:41:35 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/13 15:48:56 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*s2;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1)
		return (NULL);
	if (!set || !*s1)
		return (ft_strdup(s1));
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[j]) && j > i)
		j--;
	s2 = (char *)ft_calloc(sizeof(char), ((j - i) + 2));
	if (!s2)
		return (NULL);
	k = 0;
	while (i <= j)
		s2[k++] = s1[i++];
	return (s2);
}
