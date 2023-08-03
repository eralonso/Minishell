/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:47:29 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 16:44:07 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		printf("matrix[%i]:%s:\n", i, matrix[i]);
		i++;
	}
}

void	print_matrix_size(char **matrix, int size)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < size)
	{
		if (matrix[i])
			printf("matrix[%i]:%s:\n", i, matrix[i]);
		i++;
	}
}
