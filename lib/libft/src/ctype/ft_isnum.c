/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:08:58 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/24 10:49:49 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

int	ft_isnum(char *input, int space)
{
	int	i;

	i = 0;
	if (!input || !*input)
		return (0);
	if (ft_strchr("+-", input[0]) && ft_strchr("+-", input[1]))
		return (0);
	while (space && ft_isspace(input[i]))
		i++;
	if (ft_strchr("+-", input[i]))
		i++;
	if (!input[i])
		return (0);
	while (input[i])
	{
		if (!ft_isdigit(input[i]) && !(space && ft_isspace(input[i])))
			return (0);
		i++;
	}
	return (1);
}
