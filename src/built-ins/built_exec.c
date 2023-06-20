/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:23:30 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/20 18:31:05 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	exec_builtins(t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->args[0], 0XFFFFFF))
		if (exec_echo(&cmd->args[1]))
			return (ERR_NODE);
	if (!ft_strncmp("cd", cmd->args[0], 0XFFFFFF))
		if (exec_cd(&cmd->args[1]))
			return (ERR_NODE);
	if (!ft_strncmp("pwd", cmd->args[0], 0XFFFFFF))
		if (exec_pwd())
			return (ERR_NODE);
	if (!ft_strncmp("export", cmd->args[0], 0XFFFFFF))
		if (exec_export(&cmd->args[1]))
			return (ERR_NODE);
	if (!ft_strncmp("unset", cmd->args[0], 0XFFFFFF))
		if (exec_unset(&g_msh.env, cmd->args))
			return (ERR_NODE);
	if (!ft_strncmp("env", cmd->args[0], 0XFFFFFF))
		if (print_env(&g_msh.env))
			return (ERR_NODE);
	if (!ft_strncmp("exit", cmd->args[0], 0XFFFFFF))
		if (exec_exit(&cmd->args[1]))
			return (ERR_NODE);
	return (0);
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
