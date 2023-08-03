/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:47:59 by pramos-m          #+#    #+#             */
/*   Updated: 2023/07/13 16:43:43 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	if (ft_printf(1, "%s\n", pwd) == -1)
	{
		free(pwd);
		return (1);
	}
	free(pwd);
	return (0);
}
