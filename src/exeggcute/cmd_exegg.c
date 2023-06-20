/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exegg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:35:13 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/20 18:28:53 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	expand_args(t_cmd *cmd, t_token **tk)
{
	t_token	*tmp;
	int		i;

	if (!tk)
		return (1);
	// dprintf(2, "expand_arg: size == %i\n", tk_tkcounter(tk, ARG, EOCL, 0));
	cmd->args = ft_calloc(sizeof(char *), tk_tkcounter(tk, ARG, EOCL, 0) + 1);
	if (!cmd->args)
		return (1);
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
	int		err;
	char	**env;

	err = 0;
	if (is_builtin(cmd->args[0]))
		exec_builtins(cmd);
	cmd->path = search_cmd_path(cmd, &err);
	if (err)
		exit (1);
	env = list_to_array(&g_msh.env);
	if (!env)
		exit(1);
	execve(cmd->path, cmd->args, env);
	ft_printf(2, "Minishell: execve error\n");
	exit (1);
}

char	*search_cmd_path(t_cmd *cmd, int *err)
{
	char	*path;
	char	*env;

	path = NULL;
	env = env_node_value(&g_msh.env, "PATH");
	if (env && !ft_strchr(cmd->args[0], '/'))
		path = x_path(cmd, env, err);
	if (path)
		return (path);
	if (ft_strchr(cmd->args[0], '/') && !access(cmd->args[0], F_OK) \
		&& access(cmd->args[0], X_OK))
		ft_printf(2, "Minishell: %s: Permission denied\n", path);
	else if (ft_strchr(cmd->args[0], '/') && !access(cmd->args[0], F_OK) \
		&& !access(cmd->args[0], X_OK))
		return (ft_strdup(cmd->args[0]));
	ft_printf(2, "Minishell: %s: command not found\n", cmd->args[0]);
	return (NULL);
}

char	*x_path(t_cmd *cmd, char *env, int *err)
{
	char	**paths;
	char	*path;
	int		i;

	(1 && (paths = path_split(env)) && (i = -1));
	if (!paths)
		return ((*err = 2), NULL);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd->args[0]);
		if (!path)
			return ((*err = 2), ft_free(paths, 1));
		if (!access(path, F_OK))
		{
			if (access(path, X_OK))
			{
				ft_printf(2, "Minishell: %s: Permission denied\n", path);
				*err = 1;
				return (ft_free(paths, 1), ft_free(&path, 2));
			}
			return (ft_free(paths, 1), path);
		}
		ft_free(&path, 2);
	}
	return ((*err = 1), ft_free(paths, 1));
}

char	**path_split(char *env)
{
	char	**ret;
	char	*tmp;
	int		i;

	(1 && (ret = ft_split(env, ':')) && (i = -1));
	if (!ret)
		return (NULL);
	while (ret[++i])
	{
		tmp = ft_strchrjoin(ret[i], '/', SUFFIX);
		if (!tmp)
			return (ft_free(ret, 1));
		ft_free(&ret[i], 2);
		ret[i] = tmp;
	}
	return (ret);
}
