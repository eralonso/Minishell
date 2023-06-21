/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:40:59 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/21 10:44:05 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	**ft_matrixdup(char **matrix)
{
	char	**dup;
	int		i;

	if (!matrix)
		return (NULL);
	i = -1;
	dup = ft_calloc(sizeof(char *), ft_matrixlen(matrix) + 1);
	if (!dup)
		return (NULL);
	while (matrix[++i])
	{
		dup[i] = ft_strdup(matrix[i]);
		if (!dup[i])
			return (ft_free(dup, 1));
	}
	return (dup);
}
