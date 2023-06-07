/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:30:26 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/07 13:39:04 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_env	*env_search(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	if (!env || !key || !(*key) || !tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, 0xffffffff))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	exec_unset(t_env **env, char *node)
{
	t_env	*tmp;

	tmp = *env;
	env_unset_node(tmp, node);
	return (0);
}

void	env_unset_node(t_env *env, char	*node)
{
	env = env_search(&env, node);
	if (env == NULL)
		return ;
	else
	{
		if (env->next && env->prev)
		{
			env->prev->next = env->next;
			env->next->prev = env->prev;
		}
		else if (env->next && !env->prev)
		{
			g_msh.env = env->next;
			g_msh.env->prev = NULL;
		}
		else
			env->prev->next = NULL;
	}
	if (env->key)
		free (env->key);
	if (env->value && *env->value)
		free (env->value);
	free(env);
}

int	print_one_env(char *input)
{
	while (g_msh.env && ft_strncmp(g_msh.env->key, input, \
		ft_strlen(g_msh.env->key)))
		g_msh.env = g_msh.env->next;
	if (ft_strncmp(g_msh.env->key, input, ft_strlen(g_msh.env->key)))
		return (-1);
	return (ft_printf(1, "%s\n", g_msh.env->value));
}
