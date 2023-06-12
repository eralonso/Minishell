/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:53:46 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/12 13:00:52 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	exec_cd(char **input)
{
	char	*old_pwd;
	char	*pwd;
	int		flag;

	old_pwd = NULL;
	flag = 0;
	if (get_cd_dir(input, &pwd, &flag))
		return (1);
	if (exec_changed(pwd, old_pwd, &flag))
		return (1);
	return (0);
}

int	get_cd_dir(char **input, char **pwd,  int *flag)
{
	if (!input && !env_search(&g_msh.env, "HOME"))
		return (1);
	if (!input)
	{
		*pwd = env_node_value(&g_msh.env, "HOME");
		if (!*pwd)
			return (1);
	}
	else if (input[0] && !ft_strncmp(input[0], "-", 0XFFFFFF))
	{
		if (!env_node_value(&g_msh.env, "OLDPWD"))
			return (ft_printf(2, "Minishell: cd: OLDPWD not set\n"));
		*pwd = env_node_value(&g_msh.env, "OLDPWD");
		*flag = 1;
	}
	else if (input[0])
	{
		*pwd = *input;
	}
	return (0);
}

int	exec_changed(char *pwd, char *old_pwd, int	*flag)
{
	t_env	*tmp;

	tmp = g_msh.env;
	old_pwd = ft_calloc(sizeof(char), PATH_MAX);
	if (!old_pwd)
		return (1);
	if (!getcwd(old_pwd, PATH_MAX))
		return (1);
	if (chdir(pwd) == -1)
	{
		printf("invalid path");
		ft_free(&old_pwd, 2);
		exit(1);
	}
	else
	{
		if (env_pwd_change(&g_msh.env, pwd, old_pwd, flag))
			exit(1);
	}
	return (0);
}

int	env_pwd_change(t_env **env, char *pwd, char *old_pwd, int *flag)
{
	t_env		*tmp;

	if (!env || !pwd || !old_pwd)
		return (1);
	pwd = ft_calloc(sizeof(char), PATH_MAX);
	if (!pwd)
		return (ft_free(&old_pwd, 2), 1);
	if (!getcwd(pwd, PATH_MAX))
		return (ft_free(&old_pwd, 2), 1);
	if (*flag)
		ft_printf(1, "%s\n", pwd);
	tmp = env_search(&g_msh.env, "PWD");
	if (!tmp)
		return (ft_free(&pwd, 2), ft_free(&old_pwd, 2), 1);
	else
		tmp->value = pwd;
	tmp = *env;
	tmp = env_search(&g_msh.env, "OLDPWD");
	if (!tmp)
		return (ft_free(&pwd, 2), ft_free(&old_pwd, 2), 1);
	else
		tmp->value = old_pwd;
	return (0);
}

char	*env_node_value(t_env **env, char *key)
{
	t_env	*tmp;

	if (!env || !key || !(*key))
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, 0xffffffff))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
