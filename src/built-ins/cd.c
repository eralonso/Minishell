/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:53:46 by pramos-m          #+#    #+#             */
/*   Updated: 2023/09/09 15:57:34 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	exec_cd(char **input)
{
	char	*pwd;
	int		flag;
	int		err;

	flag = 0;
	if (input[0] && !input[0][0])
		return (0);
	err = check_max_path(input[0]);
	if (err == -1)
	{
		msg_error(MLC, NULL, NULL, 0);
		return (1);
	}
	if (err)
	{
		msg_error("cd", input[0], "File name too long", 0);
		return (1);
	}
	if (get_cd_dir(input, &pwd, &flag))
		return (1);
	if (exec_changed(pwd, &flag))
		return (1);
	return (0);
}

int	get_cd_dir(char **input, char **pwd, int *flag)
{
	if (!input[0] && !env_search(&g_msh.env, "HOME"))
		return (1);
	if (!input[0])
	{
		*pwd = env_node_value(&g_msh.env, "HOME");
		if (!*pwd)
			return (1);
	}
	else if (input[0] && !ft_strncmp(input[0], "-", 0XFFFFFF))
	{
		if (!env_node_value(&g_msh.env, "OLDPWD"))
			return (msg_error("cd", "OLDPWD not set", NULL, 0), 1);
		*pwd = env_node_value(&g_msh.env, "OLDPWD");
		*flag = 1;
	}
	else if (input[0])
		*pwd = *input;
	return (0);
}

int	exec_changed(char *pwd, int	*flag)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, PATH_MAX);
	if (!old_pwd)
		return (1);
	if (chdir(pwd) == -1)
	{
		if (access(pwd, F_OK))
			msg_error("cd", pwd, NFD, 0);
		else if (access(pwd, R_OK))
			msg_error("cd", pwd, PERM, 0);
		else
			msg_error("cd", pwd, NAD, 0);
		ft_free(&old_pwd, 2);
		return (1);
	}
	else
	{
		if (env_pwd_change(&g_msh.env, old_pwd, flag))
			return (ft_free(&old_pwd, 2), 1);
	}
	free(old_pwd);
	return (0);
}

int	env_pwd_change(t_env **env, char *old_pwd, int *flag)
{
	char		*pwd;

	if (!env || !old_pwd)
		return (1);
	pwd = getcwd(NULL, PATH_MAX);
	if (!pwd)
		return (1);
	if (*flag)
		ft_printf(1, "%s\n", pwd);
	if (node_update("PWD", pwd, EQUAL))
	{
		free(pwd);
		return (1);
	}
	free(pwd);
	if (node_update("OLDPWD", old_pwd, EQUAL))
		return (1);
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
