/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:47:59 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/26 10:51:06 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    <msh.h>

int	ft_pwd(char *input)
{
	if (!ft_strncmp(&input[0], "PWD", ft_strlen(&input[0])))
		if (print_one_env("PWD") == -1)
			return (1);
	return (0);
}

int	print_one_env(char *input)
{
	while (g_msh.env && ft_strncmp(g_msh.env->key, input, \
		ft_strlen(g_msh.env->key)))
		g_msh.env = g_msh.env->next;
	if (ft_strncmp(g_msh.env->key, input, ft_strlen(g_msh.env->key)))
		return (-1);
	return (ft_printf(1, "%s\n", g_msh.env->value));
}
