/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:25:13 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/20 11:38:32 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	*ft_matrixjoin(char **matrix, char c)
{
	int		i;
	char	*str;
	char	*tmp;

	if (!matrix)
		return (NULL);
	i = -1;
	str = NULL;
	while (matrix[++i])
	{
		str = ft_malloc_strjoin(str, matrix[i]);
		if (!str)
			return (NULL);
		(matrix[i + 1] && (tmp = str));
		(matrix[i + 1] && (str = ft_strchrjoin(str, c, SUFFIX)));
		(matrix[i + 1] && (ft_free(&tmp, 2)));
		if (!str)
			return (NULL);
	}
	return (str);
}
