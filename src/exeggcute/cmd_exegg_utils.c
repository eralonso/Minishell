/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exegg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:34:04 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 16:43:11 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

t_list	*real_list(t_token **tk)
{
	t_list	*list;
	t_list	*new;
	t_token	*tmp;

	if (!tk)
		return (NULL);
	tmp = *tk;
	list = NULL;
	while (tmp)
	{
		new = subarg_expand(tmp);
		if (!new)
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		ft_lstadd_back(&list, new);
		tmp = tmp->next;
	}
	return (list);
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

char	*x_path(t_cmd *cmd, char *env)
{
	char	**paths;
	char	*path;
	int		i;

	i = -1;
	paths = path_split(env);
	if (!paths)
		msh_exit(msg_error(MLC, 0, 0, 0));
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd->args[0]);
		if (!path)
			msh_exit((!ft_free(paths, 1)) == msg_error(MLC, 0, 0, 0));
		if (!access(path, F_OK))
		{
			if (access(path, X_OK))
			{
				msg_error(path, PERM, ft_free(paths, 1), !!ft_free(&path, 2));
				msh_exit(ERR_XPERM);
			}
			return (ft_free(paths, 1), path);
		}
		ft_free(&path, 2);
	}
	return (ft_free(paths, 1));
}

char	*t_path(char *path)
{
	if (access(path, F_OK))
	{
		msg_error(path, NFD, NULL, 0);
		msh_exit(ERR_CNF);
	}
	if (access(path, X_OK))
	{
		msg_error(path, PERM, NULL, 0);
		msh_exit(ERR_XPERM);
	}
	return (ft_strdup(path));
}
