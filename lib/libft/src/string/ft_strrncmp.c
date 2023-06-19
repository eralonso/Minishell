/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:03:27 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/19 14:43:57 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

int	ft_strrncmp(char *s1, char *s2, size_t n)
{
	int	s1_len;
	int	s2_len;

	if (!n || !s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!s1_len || !s2_len)
		return (*s1 - *s2);
	while (s1[s1_len - 1] && s2[s2_len - 1] && --n)
	{
		if (s1[s1_len - 1] != s2[s2_len - 1])
			return (s1[s1_len - 1] - s2[s2_len - 1]);
		s1_len--;
		s2_len--;
	}
	return (s1[s1_len - 1] - s2[s2_len - 1]);
}
