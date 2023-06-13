/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 10:21:00 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/13 15:34:43 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

int	ft_atoi(const char *str)
{
	int		res;
	int		sign;
	int		i;
	char	*base;

	((i = 0) || (res = 0) || (sign = 1));
	base = B10;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strnstr(str, "0X", 2) || ft_strnstr(str, "0x", 2))
	{
		base = BU16;
		i += 2;
	}
	while (str[i] && ft_strchr(base, ft_toupper(str[i++])))
		res = (ft_toupper(str[i - 1]) - ('0' + (7 \
		* ft_isalpha(str[i - 1])))) + (res * ft_strlen(base));
	return (res * sign);
}
