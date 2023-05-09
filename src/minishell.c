/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/09 19:03:26 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

char	**list_to_array(t_env *m_env)
{
	char		**res;
	static char	equal[2] = {'=', '\0'};
	int			i;

	i = 0;
	while (m_env && m_env->next && ++i)
		m_env = m_env->next;
	if (m_env)
		i++;
	res = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!res)
		return (NULL);
	while (m_env && --i >= 0)
	{
		res[i] = ft_strjoin(m_env->key, equal);
		if (!res[i])
			return (ft_free(res, 1));
		res[i] = ft_malloc_strjoin(res[i], m_env->value);
		if (!res[i])
			return (ft_free(res, 1));
		m_env = m_env->prev;
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
			exit(1);// error_handler (NULL);
		tmp = node_create(res[0], res[1]);
		if (!tmp)
			exit(1);// error_handler (NULL);
		addfront_env(&g_msh.env, tmp);
		free(res);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) ac;
	(void) av;
	(void) env;
	if (ac > 1)
		exit(1);
	ft_env(env);
	while (42)
	{
		line = readline("PESH + 🐚 > ");
		if (!line)
			break ;
	}
	return (0);
}
