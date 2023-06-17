/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:23:30 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/17 17:02:15 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	exec_builtins(t_cmd *cmd)
{
	if (ft_strncmp("echo", cmd->cmd_args[0], 0XFFFFFF))
		if (exec_echo(cmd->cmd_args))
			return (ERR_NODE);
	if (ft_strncmp("cd", cmd->cmd_args[0], 0XFFFFFF))
		if (exec_cd(cmd->cmd_args))
			return (ERR_NODE);
	if (ft_strncmp("pwd", cmd->cmd_args[0], 0XFFFFFF))
		if (exec_pwd())
			return (ERR_NODE);
	if (ft_strncmp("export", cmd->cmd_args[0], 0XFFFFFF))
		if (exec_export(cmd->cmd_args))
			return (ERR_NODE);
	if (ft_strncmp("unset", cmd->cmd_args[0], 0XFFFFFF))
		if (exec_unset(&g_msh.env, cmd->cmd_args))
			return (ERR_NODE);
	if (ft_strncmp("env", cmd->cmd_args[0], 0XFFFFFF))
		if (print_env(&g_msh.env))
			return (ERR_NODE);
	if (ft_strncmp("exit", cmd->cmd_args[0], 0XFFFFFF))
		if (exec_exit(cmd->cmd_args))
			return (ERR_NODE);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp("echo", cmd, 0XFFFFFF))
		return (1);
	else if (ft_strncmp("cd", cmd, 0XFFFFFF))
		return (1);
	else if (ft_strncmp("pwd", cmd, 0XFFFFFF))
		return (1);
	else if (ft_strncmp("export", cmd, 0XFFFFFF))
		return (1);
	else if (ft_strncmp("unset", cmd, 0XFFFFFF))
		return (1);
	else if (ft_strncmp("env", cmd, 0XFFFFFF))
		return (1);
	else if (ft_strncmp("exit", cmd, 0XFFFFFF))
		return (1);
	else
		return (0);
}
