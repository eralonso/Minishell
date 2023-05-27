/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:30:26 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/27 12:59:08 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_env	*env_search(t_env *env, char *key)
{
	if (!env || !key || !(*key))
		return (NULL);
	while (env && env->next)
	{
		if (!ft_strncmp(env->key, key, 0xffffffff))
			return (env);
		env = env->next;
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
	env = env_search(env, node);
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

int	ft_pwd(char *input)
{
	if (!ft_strncmp(&input[0], "PWD", ft_strlen(&input[0])))
		if (print_one_env("PWD") == -1)
			return (1);
	return (0);
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
