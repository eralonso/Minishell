/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:30:26 by pramos-m          #+#    #+#             */
/*   Updated: 2023/07/13 16:43:11 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

t_env	*env_search(t_env **env, char *key)
{
	t_env	*tmp;

	if (!env || !key || !(*key))
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, 0xffffffff))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	exec_unset(t_env **env, char **input)
{
	int		j;
	int		size;
	int		err;
	int		ret;

	j = -1;
	ret = 0;
	size = ft_matrixlen(input);
	while (++j < size)
	{
		err = check_unset(input[j]);
		if (err == -1)
			return (1);
		if (err)
			ret = 1;
		if (!err)
			env_unset_node(env, input[j]);
	}
	return (ret);
}

void	env_unset_node(t_env **env, char *node)
{
	t_env	*tmp;

	tmp = env_search(env, node);
	if (tmp == NULL)
		return ;
	if (tmp->next && tmp->prev)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	else if (tmp->next && !tmp->prev)
	{
		g_msh.env = tmp->next;
		g_msh.env->prev = NULL;
	}
	else
		tmp->prev->next = NULL;
	if (tmp->key)
		free (tmp->key);
	if (tmp->value && *tmp->value)
		free (tmp->value);
	free(tmp);
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
