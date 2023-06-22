/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exegg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:35:13 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/22 12:04:40 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	expand_args(t_cmd *cmd, t_token **tk)
{
	t_token	*tmp;
	int		i;

	if (!tk)
		return (1);
	cmd->args = ft_calloc(sizeof(char *), tk_tkcounter(tk, ARG, EOCL, 0) + 1);
	if (!cmd->args)
		return (1);
	if (!(*tk)->args)
		return (0);
	tmp = *tk;
	i = 0;
	while (tmp)
	{
		cmd->args[i] = subarg_expand(tmp);
		if (!cmd->args[i])
			return (1);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

void	exec_cmd(t_cmd *cmd)
{
	char	**env;

	if (is_builtin(cmd->args[0]))
		msh_exit(exec_builtins(cmd));
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
	return (NULL);
}
