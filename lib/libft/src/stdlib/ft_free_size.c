/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:32:27 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 11:35:40 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_free_size(char **matrix, int size)
{
	int	i;

	if (!matrix)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		if (matrix[i])
			free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
	return (NULL);
}
