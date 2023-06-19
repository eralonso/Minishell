/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:47:59 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/19 16:40:47 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    <msh.h>

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
