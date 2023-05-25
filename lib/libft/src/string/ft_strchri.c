/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:48:19 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/16 15:14:00 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strchri(const char *s, int c)
{
	int	i;
	
	if (!s)
		return (-2);
	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	return (-1);
}
