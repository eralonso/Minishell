/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixjoin_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:21:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 11:35:34 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_matrixjoin_size(char **matrix, char c, int size)
{
	int		i;
	int		rem;
	char	*str;
	char	*tmp;

	if (!matrix || size <= 0)
		return (NULL);
	(1 && (i = -1) && ((str = NULL)));
	rem = ft_matrix_remainder(matrix, size);
	while (++i < size)
	{
		if (matrix[i])
		{
			str = ft_malloc_strjoin(str, matrix[i]);
			if (!str)
				return (NULL);
			(1 && (--rem) && (tmp = str));
			(rem && (str = ft_strchrjoin(str, c, SUFFIX)));
			(rem && ft_free(&tmp, 2));
			if (!str)
				return (NULL);
		}
	}
	return (str);
}
