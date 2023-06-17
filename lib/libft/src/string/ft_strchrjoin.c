/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:21:34 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/17 10:32:23 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	*ft_strchrjoin(char *str, char c, int mode)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	if (!new)
		return (NULL);
	if (mode == PREFIX)
		new[++j] = c;
	if (str)
	{
		while (str[++i])
			new[++j] = str[i];
	}
	if (mode == SUFFIX)
		new[++j] = c;
	return (new);
}