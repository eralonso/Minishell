/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:06:33 by pramos-m          #+#    #+#             */
/*   Updated: 2023/07/13 11:35:40 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_strcat(char *dst, const char *src)
{
	int	i;
	int	j;

	if (!dst || !src)
		return ;
	j = 0;
	i = ft_strlen(dst);
	while (src[j])
		dst[i++] = src[j++];
}
