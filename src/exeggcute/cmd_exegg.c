/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exegg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:35:13 by eralonso          #+#    #+#             */
/*   Updated: 2023/09/05 12:54:45 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	expand_args(t_cmd *cmd, t_token **tk)
{
	t_list	*args;
	t_list	*tmp;
	int		i;

	if (!tk)
		return (1);
	args = real_list(tk);
	if (!args)
		return (1);
	cmd->args = ft_calloc(sizeof(char *), ft_lstsize(args) + 1);
	if (!cmd->args || !(*tk)->args)
		ft_lstclear(&args, free);
	if (!cmd->args)
		return (1);
	if (!(*tk)->args)
		return (0);
	i = 0;
	while (args)
	{
		tmp = args->next;
		cmd->args[i++] = args->content;
		free(args);
		args = tmp;
	}
	return (0);
}

char	*search_cmd_path(t_cmd *cmd)
{
	char	*path;
	char	*env;

	path = NULL;
	if (!cmd->args[0][0])
		msg_error(cmd->args[0], CNF, NULL, 0);
	if (!cmd->args[0][0])
		msh_exit(ERR_CNF);
	env = env_node_value(&g_msh.env, "PATH");
	if (env && !ft_strchr(cmd->args[0], '/'))
	{
		path = x_path(cmd, env);
		if (path)
			return (path);
		msg_error(cmd->args[0], CNF, NULL, 0);
		msh_exit(ERR_CNF);
	}
	if (ft_strchr(cmd->args[0], '/'))
		return (t_path(cmd->args[0]));
	msg_error(cmd->args[0], NFD, NULL, 0);
	msh_exit(ERR_CNF);
	return (NULL);
}

static int	is_directory(char *file)
{
	DIR	*dir_check;

	dir_check = opendir(file);
	if (dir_check)
	{
		closedir(dir_check);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_cmd *cmd)
{
	char	**env;

	if (is_builtin(cmd->args[0]))
		msh_exit(exec_builtins(cmd));
	if (is_directory(cmd->args[0]))
	{
		msg_error(cmd->args[0], ISDIR, NULL, 0);
		msh_exit(ERR_XPERM);
	}
	cmd->path = search_cmd_path(cmd);
	if (!cmd->path)
		msh_exit(ERR_GEN);
	env = list_to_array(&g_msh.env);
	if (!env)
		exit(ERR_GEN);
	execve(cmd->path, cmd->args, env);
	msg_error(EVE, NULL, NULL, 0);
	msh_exit(ERR_GEN);
}
