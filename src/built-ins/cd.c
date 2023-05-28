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

	if (env_search(&g_msh.env, "PWD"))
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

int	get_cd_dir(char **input, char **pwd)
{
	if (!input[0] && !env_search(&g_msh.env, "HOME"))
		return (1);
	if (!input[0])
	{
		*pwd = env_node_value(g_msh.env, "HOME");
		if (!*pwd)
			return (1);
	}
	else if (input[0])
	{
		*pwd = *input;
	}
	return (0);
}

int	exec_changed(char *pwd, char *old_pwd)
{
	t_env	*tmp;

	tmp = g_msh.env;
	if (chdir(pwd) == -1)
	{
		printf("invalid path");
		exit(1);
	}
	else
	{
		if (env_pwd_change(&g_msh.env, pwd, old_pwd))
			exit(1);
	}
	return (0);
}

int	env_pwd_change(t_env **env, char *pwd, char *old_pwd)
{
	t_env		*tmp;

	tmp = *env;
	if (!env || !pwd || !old_pwd)
		return (1);
	tmp = env_search(&g_msh.env, "PWD");
	if (!tmp)
	{
		if (create_add_node("PWD", pwd))
			return (1);
	}
	else
		tmp->value = pwd;
	tmp = *env;
	tmp = env_search(&g_msh.env, "OLDPWD");
	if (!tmp)
	{
		if (create_add_node("OLDPWD", old_pwd))
			return (1);
	}
	else
		tmp->value = old_pwd;
	return (0);
}

char	*env_node_value(t_env *env, char *key)
{
	if (!env || !key || !(*key))
		return (NULL);
	while (env && env->next)
	{
		if (!ft_strncmp(env->key, key, 0xffffffff))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
