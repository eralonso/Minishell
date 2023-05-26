/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:00:11 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/26 17:05:57 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	exec_exit(char **exit_args)
{
	int			value;
	long long	tmp_value;

	value = g_msh.err;
	if (write(2, "exit\n", 5) < 0)
		exit(1);
	if (!validate_args(exit_args, &value) && exit_args[1])
	{
		tmp_value = ft_atoi(exit_args[0]);
		value = (int)tmp_value;
	}
	g_msh.err = value;
	if (value == -1)
		return (1);
	clean_env(&g_msh.env, 0);
	printf("exit val:%i", value);
	exit(value);
	return (0);
}

int	validate_args(char **node, int *value)
{
	int	i;

	i = 1;
	if (!node[1])
		return (0);
	while (node[i])
	{
		if (!is_valid_num(node[i]))
		{
			print_exit_error(node[i]);
			*value = 255;
			break ;
		}
		i++;
	}
	if (!node[i] && i == 2)
		return (0);
	return (1);
}

int	is_valid_num(char *data)
{
	bool	neg;

	neg = 0;
	if (!ft_isnum(data) || *data == 0)
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

int	print_exit_error(char *data)
{
	write(2, "ba.sh: exit: ", 13);
	write(2, data, ft_strlen(data));
	write(2, ": numeric argument required\n", 28);
	return (255);
}