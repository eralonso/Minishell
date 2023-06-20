/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_remainder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:36:43 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/20 10:38:51 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

int	ft_matrix_remainder(char **matrix, int size)
{
	int	len;
	int	i;

	if (!matrix || size <= 0)
		return (0);
	i = -1;
	len = 0;
	while (++i < size)
	{
		if (matrix[i])
			len++;
	}
	return (len);
}
