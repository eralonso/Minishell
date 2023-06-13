/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:06:27 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/13 15:36:20 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

long long	ft_atoll(char *str)
{
	long long	neg;
	long long	res;
	int			i;

	((res = 0) || (i = 0) || (neg = 1));
	if (!str || !str[i])
		return (0);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] == '-')
		neg = -1;
	if (str[i] && ft_strchr("+-", str[i]))
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * neg);
}
