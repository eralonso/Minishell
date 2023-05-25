/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:30:26 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/25 17:35:00 by pramos-m         ###   ########.fr       */
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

int	exec_export(char **nodes)
{
	if (!nodes)
		print_export();
	else
	{
		
	}
	return (0);
}

void	print_export()
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = sort_env(list_to_array(&g_msh.env));
	while (tmp[++i])
		printf("declare -x %s\n", tmp[i]);
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