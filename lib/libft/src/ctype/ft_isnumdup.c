/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:05:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 11:35:33 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_isnumdup(char **input, int num, int index)
{
	int	i;

	i = -1;
	if (!input || !*input)
		return (0);
	while (++i < index)
	{
		if (num == ft_atoi(input[i]))
			return (1);
	}
	return (0);
}
