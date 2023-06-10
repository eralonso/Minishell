/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/10 13:29:35 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

char	**list_to_array(t_env **m_env)
{
	char		**res;
	static char	equal[2] = {'=', '\0'};
	int			i;
	t_env		*tmp;

	(1 && ((i = 0) || 1) && (tmp = *m_env));
	while (tmp && tmp->next && ++i)
		tmp = tmp->next;
	(tmp && i++);
	res = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (tmp && ++i >= 0)
	{
		res[i] = ft_strjoin(tmp->key, equal);
		if (!res[i])
			return (ft_free(res, 1));
		res[i] = ft_malloc_strjoin(res[i], tmp->value);
		if (!res[i])
			return (ft_free(res, 1));
		tmp = tmp->prev;
	}
	return (res);
}

t_env	*node_create(char *key, char *value)
{
	t_env	*node;


	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	return (node);
}

void	addfront_env(t_env **msh_env, t_env *tmp)
{
	if (*msh_env)
	{
		tmp->next = *msh_env;
		(*msh_env)->prev = tmp;
	}
	*msh_env = tmp;
}

int	clean_env(t_env **list, int ret)
{
	t_env	*tmp;
	t_env	*top;

	(list && (tmp = *list)) || (tmp = NULL);
	while (tmp)
	{
		top = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = top;
	}
	return (ret);
}

void	ft_env(char **env)
{
	char	*res[2];
	int		i;
	int		eq;
	t_env	*tmp;

	i = -1;
	g_msh.env = NULL;
	while (env[++i])
	{
		eq = ft_strchri(env[i], '=');
		if (eq == -2)
			continue ;
		res[0] = ft_substr(env[i], 0, eq);
		if (!res[0])
			clean_env(&g_msh.env, 0);
		res[1] = ft_substr(env[i], eq + 1, ft_strlen(env[i]) - (eq + 1));
		if (!res[1])
			clean_env(&g_msh.env, ft_free(&res[0], 2) == NULL);
		tmp = node_create(res[0], res[1]);
		if (!tmp)
			clean_env(&g_msh.env, !ft_free(&res[0], 2) | !ft_free(&res[1], 2));
		addfront_env(&g_msh.env, tmp);
	}
}
