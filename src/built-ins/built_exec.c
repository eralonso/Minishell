/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:23:30 by pramos-m          #+#    #+#             */
/*   Updated: 2023/09/05 13:02:46 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	exec_builtins(t_cmd *cmd)
{
	int		ret;
	char	*str;

	str = ft_strdup(cmd->args[0]);
	if (!str)
		return (-1);
	ft_strtolower(str);
	ret = 0;
	if (!ft_strncmp("echo", str, 0XFFFFFF))
		ret = exec_echo(&cmd->args[1]);
	if (!ft_strncmp("cd", str, 0XFFFFFF))
		ret = exec_cd(&cmd->args[1]);
	if (!ft_strncmp("pwd", str, 0XFFFFFF))
		ret = exec_pwd();
	if (!ft_strncmp("export", str, 0XFFFFFF))
		ret = exec_export(&cmd->args[1]);
	if (!ft_strncmp("unset", str, 0XFFFFFF))
		ret = exec_unset(&g_msh.env, cmd->args);
	if (!ft_strncmp("env", str, 0XFFFFFF))
		ret = print_env(&g_msh.env);
	if (!ft_strncmp("exit", str, 0XFFFFFF))
		ret = exec_exit(&cmd->args[1]);
	free(str);
	return (ret);
}

int	is_builtin(char *cmd)
{
	char	*str;

	if (!cmd)
		return (0);
	str = ft_strdup(cmd);
	if (!str)
		return (-1);
	if (env_search(&g_msh.env, "PATH") && ft_strnstr(\
		env_search(&g_msh.env, "PATH")->value, "/bin", 0xFFFFFF))
		ft_strtolower(str);
	if (!ft_strncmp("echo", str, 0XFFFFFF))
		return (free(str), 1);
	else if (!ft_strncmp("cd", str, 0XFFFFFF))
		return (free(str), 1);
	else if (!ft_strncmp("pwd", str, 0XFFFFFF))
		return (free(str), 1);
	else if (!ft_strncmp("export", str, 0XFFFFFF))
		return (free(str), 1);
	else if (!ft_strncmp("unset", str, 0XFFFFFF))
		return (free(str), 1);
	else if (!ft_strncmp("env", str, 0XFFFFFF))
		return (free(str), 1);
	else if (!ft_strncmp("exit", str, 0XFFFFFF))
		return (free(str), 1);
	return (free(str), 0);
}
