/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:56:31 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/20 14:17:36 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	kill_childs(pid_t *pids, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pids[i] > 0)
		{
			kill(pids[i], SIGTERM);
			pids[i] = 0;
		}
	}
	return (1);
}

int	wait_childs(pid_t *pids, int size)
{
	int		status;
	int		aux;
	int		i;
	int		last;

	if (pids[0] == 0)
		return (0);
	i = -1;
	last = 0;
	while (++i < size)
	{
		aux = waitpid(-1, &status, 0);
		if (aux == -1)
			return (1);
		if (WIFEXITED(status) && aux == pids[size - 1])
			(1 && (last = 1) && (g_msh.err = WEXITSTATUS(status)));
		else if (WIFSIGNALED(status))
		{
			if (!last && WTERMSIG(status) == SIGINT)
				g_msh.err = 130;
			else if (!last && WTERMSIG(status) == SIGQUIT)
				g_msh.err = 131;
		}
	}
	return (0);
}

pid_t	exec_node(t_lstt *node, int idx, int end)
{
	pid_t	child;

	if (redirect_parser(node->redirect, node->redir_size))
		return (ERR_NODE);
	if (redirect_node(node))
		return (ERR_NODE);
	child = 0;
	(void) idx;
	(void) end;
	if (node->type == STAIR)
	{
		child = fork();
		if (child < 0)
			return (ERR_NODE);
		if (child == 0)
		{
			executor(node->content);
			exit(g_msh.err);
		}
		return (child);
	}
	init_signals(N_INTERACT);
	if (expand_args((t_cmd *)node->content, &((t_cmd *)node->content)->args_tk))
		return (ERR_NODE);
	if (idx == 0 && end && is_builtin(((t_cmd *)node->content)->args[0]))
		return (exec_builtins(node->content));
	child = fork();
	if (child < 0)
		return (ERR_NODE);
	if (child == 0)
		exec_cmd((t_cmd *)node->content);
	return (child);
}

void	exec_cmd(t_cmd *cmd)
{
	int		err;

	if (is_builtin(cmd->args[0]))
		exec_builtins(cmd);
	cmd->path = search_cmd_path(cmd, &err);
	if (err)
		exit (1);
	// if (cmd->path)
		// execve();
}

char	*search_cmd_path(t_cmd *cmd, int *err)
{
	char	*path;
	char	*env;

	env = env_node_value(&g_msh.env, "PATH");
	if (env && !ft_strchr(cmd->args[0], '/'))
		path = x_path(cmd, env, err);
	// if (ft_strchr(cmd->args[0], '/'))
	// {
		
	// }
	return (path);
}

char	*x_path(t_cmd *cmd, char *env, int *err)
{
	char	**paths;
	char	*path;
	int		i;

	(1 && (i = -1) && (paths = path_split(cmd, env)));
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

char	**path_split(t_cmd *cmd, char *env)
{
	char	**ret;
	char	*tmp;
	int		i;

	(1 && (i = -1) && (ret = ft_split(env, ':')));
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

int	exec_nodes(t_lstt **node, int size, const int std_fd[2])
{
	t_lstt		*tmp;
	pid_t		*pids;
	int			i;
	int			tmp_fd[2];

	pids = ft_calloc(sizeof(pid_t), size);
	if (!node || !*node || !pids)
		return (1);
	(1 && (tmp = *node) && (i = 0));
	(1 && (tmp_fd[0] = dup(std_fd[0])) && (tmp_fd[1] = dup(std_fd[1])));
	if (tmp_fd[0] == -1 || tmp_fd[1] == -1)
		return (free(pids), 1);
	while (tmp)
	{
		if (pipe(tmp->fd) == -1)
			return (exec_clean(tmp_fd, std_fd, pids, size));
		pids[i] = exec_node(tmp, i, i == (size - 1));
		if (pids[i++] == ERR_NODE)
			return (exec_clean(tmp_fd, std_fd, pids, size));
		tmp = tmp->next;
	}
	(((redir_std(tmp_fd, std_fd) || wait_childs(pids, size)) \
	&& (i = kill_childs(pids, size))) || (i = 0));
	return (free(pids), i);
}

int	executor(t_stair *st)
{
	const int	std_fd[2] = {0, 1};

	if (!st)
		return (0);
	if (st->type != MAIN)
		if (executor(st->step))
			return (1);
	if ((st->type == AND && g_msh.err) || (st->type == OR && !g_msh.err))
		return (0);
	if (exec_nodes(&st->node, st->size, std_fd))
		return (1);
	return (0);
}
