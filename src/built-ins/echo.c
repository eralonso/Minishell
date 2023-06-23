/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:07:59 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/23 18:29:29 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

static int	check_echo_flag(char *str);

int	exec_echo(char **input)
{
	int		i;
	char	c;

	i = -1;
	c = ' ';
	if (input[0] && check_echo_flag(input[0]))
	{
		if (ft_echo_n(input))
			return (1);
	}
	else
	{
		while (input && input[++i])
		{
			if (!input[i + 1])
				c = '\n';
			if (ft_printf(1, "%s%c", input[i], c) == -1)
				return (1);
		}
		if (!input[0] && ft_printf(1, "\n") == -1)
			return (1);
	}
	return (0);
}

static int	check_echo_flag(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 0;
	while (str[++i] == 'n')
		;
	return (str[i] == '\0');
}

int	ft_echo_n(char **input)
{
	int		i;
	char	c;

	i = 0;
	c = ' ';
	while (check_echo_flag(input[i]))
		i++;
	while (input[i])
	{
		if (!input[i + 1])
			c = '\0';
		if (ft_printf(1, "%s%c", input[i], c) == -1)
		{
			g_msh.err = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
