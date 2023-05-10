/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/10 12:03:23 by pramos-m         ###   ########.fr       */
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
	node->prev = NULL;
	node->next = NULL;
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

void	ft_env(char **env)
{
	char	**res;
	int		i;
	t_env	*tmp;

	i = -1;
	g_msh.env = NULL;
	while (env[++i])
	{
		res = ft_split(env[i], '=');
		if (!res)
			exit(1); // error_handler (NULL);
		tmp = node_create(res[0], res[1]);
		if (!tmp)
			exit(1); // error_handler (NULL);
		addfront_env(&g_msh.env, tmp);
		free(res);
	}
}
