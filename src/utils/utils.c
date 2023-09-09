/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:10:43 by eralonso          #+#    #+#             */
/*   Updated: 2023/09/09 16:01:56 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	init_kof(t_kof *fok)
{
	fok->and = 0;
	fok->or = 0;
	fok->dq = -1;
	fok->sq = -1;
	fok->cp = 0;
	fok->op = 0;
	return (1);
}

// void	env_set_value(t_env **list, char *name, char *value)
// {
// 	t_env	*env;
// 	char	**input;

// 	input = calloc(sizeof(char *), 3);
// 	input[0] = name;
// 	input[1] = value;
// 	if (!list || !name || !value || !*list)
// 		return ;
// 	env = env_search(list, name);
// 	if (env == NULL)
// 		export_add(input);
// 	else
// 	{
// 		free (env->value);
// 		env->value = ft_strdup(value);
// 	}
// }

int	env_change_value(t_env	*list, char *name, char *value)
{
	t_env	*node;

	node = env_search(&list, name);
	if (!node)
		return (0);
	free(node->value);
	if (value == NULL)
		node->value = NULL;
	else
	{
		node->value = ft_substr(value, 0, 0xffffffff);
		if (!node->value)
			return (1);
	}
	return (0);
}

int	create_add_node(char *key, char *value)
{
	t_env	*env;
	char	*tmp;
	char	*tmp2;

	(0 || (tmp = NULL) || (tmp2 = NULL));
	if (key)
	{
		tmp = ft_strdup(key);
		if (!tmp)
			return (1);
	}
	if (value)
	{
		tmp2 = ft_strdup(value);
		if (!tmp2)
			return (free(tmp), 1);
	}
	env = node_create(tmp, tmp2);
	if (!env)
		return (ft_free(&tmp, 2), ft_free(&tmp2, 2), 1);
	addfront_env(&g_msh.env, env);
	return (0);
}
