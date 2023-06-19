/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:30:26 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/19 15:54:12 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

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

	j = -1;
	while (++j < ft_matrixlen(input))
	{
		if (!check_unset(input[j]))
			return (1);
		env_unset_node(env, input[j]);
	}
	return (0);
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
	t_env	*tmp;

	tmp = g_msh.env;
	while (tmp && ft_strncmp(tmp->key, input, 0XFFFFFF))
		tmp = tmp->next;
	if (tmp && ft_printf(1, "%s\n", tmp->value) == -1)
		return (-1);
	return (0);
}
