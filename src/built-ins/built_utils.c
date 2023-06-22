/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:42:55 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/22 12:48:31 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    <msh.h>

int	check_export(char *key, char *str)
{
	int	i;

	i = 0;
	if (!*key || (key && ft_isdigit(key[0])))
	{
		if (msg_error("export", str, NVI, 2) == -1)
			return (0);
		return (0);
	}
	while (key && key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			if (msg_error("export", str, NVI, 2) == -1)
				return (0);
			return (0);
		}
		i++;
	}
	return (1);
}

int	sec_check_export(char *key)
{
	int	i;

	i = 0;
	if (!*key || (key && ft_isdigit(key[0])))
		return (0);
	while (key && key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_unset(char *node)
{
	int	i;

	i = 0;
	if (ft_isdigit(node[0]))
	{
		if (msg_error("unset", node, NVI, 2) == -1)
			return (-1);
		return (1);
	}
	while (node[i])
	{
		if (!ft_isalnum(node[i]) && node[i] != '_')
		{
			if (msg_error("unset", node, NVI, 2) == -1)
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}
