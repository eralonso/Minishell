/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:00:11 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/24 10:54:30 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

static int	validate_args(char **node);
static void	print_exit_error(char *data);

int	exec_exit(char **exit_args)
{
	int			value;
	long long	tmp_value;

	value = g_msh.err;
	if (ft_printf(2, "exit\n") < 0)
		exit(1);
	if (!exit_args[0])
		exit(g_msh.err);
	if (!validate_args(exit_args))
	{
		tmp_value = ft_atoi(exit_args[0]);
		value = (int)tmp_value;
	}
	if (ft_matrixlen(exit_args) > 1)
		return (msg_error("exit", "too many arguments", NULL, 0), 1);
	msh_exit(value);
	return (0);
}

static int	validate_args(char **node)
{
	int	i;

	i = 0;
	if (!node[0])
		return (1);
	while (node[i])
	{
		if (!is_valid_num(node[i]))
			print_exit_error(node[i]);
		i++;
	}
	if (!node[i] && i == 2)
		return (1);
	return (0);
}

int	is_valid_num(char *data)
{
	bool	neg;

	neg = 0;
	if (!ft_isnum(data, 1) || *data == 0)
		return (0);
	if (*data == '-')
		neg = 1;
	if (*data == '-' || *data == '+')
		data++;
	while (*data && *(data + 1) && *data == '0')
		data++;
	if (ft_strlen(data) > 19)
		return (0);
	if (ft_strlen(data) < 19)
		return (1);
	if (!neg && ft_strncmp(data, "9223372036854775807", 0xffffffff) <= 0)
		return (1);
	if (neg && ft_strncmp(data, "9223372036854775808", 0xffffffff) <= 0)
		return (1);
	return (0);
}

static void	print_exit_error(char *data)
{
	if (msg_error("exit", data, NAR, 0))
		msh_exit(1);
	msh_exit(255);
}
