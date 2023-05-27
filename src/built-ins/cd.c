/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:53:46 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/27 17:58:43 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	exec_cd(char **input)
{
	char	*old_pwd;
	char	*pwd;

	if (env_search(g_msh.env, "PWD"))
	{
		old_pwd = env_node_value(g_msh.env, "PWD");
		if (!old_pwd)
			return (1);
	}
	if (get_cd_dir(input, &pwd))
		return (1);
	if (exec_changed(pwd, old_pwd))
		return (1);
	return (0);
}
