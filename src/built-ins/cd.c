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

int	exec_changed(char *pwd, char *old_pwd)
{
	if (pwd && *pwd && chdir(pwd) == -1)
		return (1);
	if (change_pwd_values(old_pwd, pwd))
		return (1);
	return (0);
}

int	change_pwd_values(char *old_pwd, char *pwd)
{
	if (old_pwd && env_search(g_msh.env, "OLDPWD"))
	{
		if (env_change_value(g_msh.env, "OLDPWD", old_pwd))
			return (1);
	}
	else if (old_pwd)
		env_set_value(&g_msh.env, "OLDPWD", old_pwd);
	else if (!old_pwd)
		env_unset_node(g_msh.env, "OLDPWD");
	if (env_search(g_msh.env, "PWD"))
		if (env_change_value(g_msh.env, "PWD", pwd))
			return (1);
	if (!env_search(g_msh.env, "PWD"))
		env_set_value(&g_msh.env, "PWD", pwd);
	return (0);
}

int	get_cd_dir(char	**node, char **pwd)
{
	if (node[0] && !node[1]
		&& !env_search(g_msh.env, "HOME"))
		return (1);
	if (node[0] && !node[1])
		*pwd = env_node_value(g_msh.env, "HOME");
	else if (node[1])
		*pwd = node[1];
	// else if (node[0] && node[1]
	// 	&& !ft_strcmp(node[1], "-"))
	// {
	// 	if (!env_search(g_msh.env, "OLDPWD"))
	// 		return (1);
	// 	*pwd = env_node_value(g_msh.env, "OLDPWD");
	// }
	if (!(*pwd))
		return (1);
	return (0);
}

char	*env_node_value(t_env *list, char *name)
{
	t_env	*env;

	if (!list || !name)
		return (NULL);
	env = env_search(list, name);
	if (env == NULL || env->value == NULL)
		return (NULL);
	return (ft_strdup(env->value));
}
