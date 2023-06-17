/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:07:59 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/17 14:12:56 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	exec_echo(char **input)
{
	int		i;
	char	c;

	i = -1;
	c = ' ';
	if (!ft_strncmp(input[0], "-n", ft_strlen(input[0])))
	{
		if (ft_echo_n(input))
			return (1);
	}
	else
	{
		while (input[++i])
		{
			if (!input[i + 1])
				c = '\n';
			if (printf("%s%c", input[i], c) == -1)
			{
				g_msh.err = 1;
				return (1);
			}
		}
	}
	return (0);
}

int	ft_echo_n(char **input)
{
	int		i;
	char	c;

	i = 0;
	c = ' ';
	while (input[++i])
	{
		if (!input[i + 1])
			c = '\0';
		if (printf("%s%c", input[i], c) == -1)
		{
			g_msh.err = 1;
			return (1);
		}
	}
	return (0);
}
