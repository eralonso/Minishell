/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:23:30 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/21 19:13:31 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	exec_builtins(t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp("echo", cmd->args[0], 0XFFFFFF))
		ret = exec_echo(&cmd->args[1]);
	if (!ft_strncmp("cd", cmd->args[0], 0XFFFFFF))
		ret = exec_cd(&cmd->args[1]);
	if (!ft_strncmp("pwd", cmd->args[0], 0XFFFFFF))
		ret = exec_pwd();
	if (!ft_strncmp("export", cmd->args[0], 0XFFFFFF))
		ret = exec_export(&cmd->args[1]);
	if (!ft_strncmp("unset", cmd->args[0], 0XFFFFFF))
		ret = exec_unset(&g_msh.env, cmd->args);
	if (!ft_strncmp("env", cmd->args[0], 0XFFFFFF))
		ret = print_env(&g_msh.env);
	if (!ft_strncmp("exit", cmd->args[0], 0XFFFFFF))
		ret = exec_exit(&cmd->args[1]);
	return (ret);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 0XFFFFFF))
		return (1);
	else if (!ft_strncmp("cd", cmd, 0XFFFFFF))
		return (1);
	else if (!ft_strncmp("pwd", cmd, 0XFFFFFF))
		return (1);
	else if (!ft_strncmp("export", cmd, 0XFFFFFF))
		return (1);
	else if (!ft_strncmp("unset", cmd, 0XFFFFFF))
		return (1);
	else if (!ft_strncmp("env", cmd, 0XFFFFFF))
		return (1);
	else if (!ft_strncmp("exit", cmd, 0XFFFFFF))
		return (1);
	else
		return (0);
}
