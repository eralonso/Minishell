/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:30:13 by eralonso          #+#    #+#             */
/*   Updated: 2023/09/09 16:30:26 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	**sort_env(char **env)
{
	int		size;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (!env || !*env)
		return (NULL);
	size = ft_matrixlen(env);
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if ((int)env[j][0] > (int)env[j + 1][0])
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

void	set_null_node(char *key, t_env **env)
{
	t_env	*tmp;

	(void)	**env;
	tmp = env_search(&g_msh.env, key);
	if (tmp)
	{
		ft_free(&tmp->value, 2);
		tmp->value = NULL;
	}
}
