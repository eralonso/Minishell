/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:31:56 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/20 10:36:22 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

void	*ft_free(char **matrix, int option)
{
	int	i;

	if (matrix && option == 1)
	{
		i = 0;
		while (matrix[i])
		{
			free(matrix[i]);
			matrix[i] = NULL;
			i++;
		}
		free(matrix);
	}
	else if (matrix && *matrix && option == 2)
	{
		free(*matrix);
		*matrix = NULL;
	}
	matrix = NULL;
	return (NULL);
}
