/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:42:55 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/10 16:15:00 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    <msh.h>

// char	**sort_env(char **env)
// {
// 	int		size;
// 	int		i;
// 	int		j;
// 	char	*tmp;

// 	i = 0;
// 	size = ft_matrixlen(env);
// 	while (i < size - 1)
// 	{
// 		j = 0;
// 		while (j < size - i - 1)
// 		{
// 			if ((int)env[j][0] > (int)env[j + 1][0])
// 			{
// 				tmp = env[j];
// 				env[j] = env[j + 1];
// 				env[j + 1] = tmp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (env);
// }

// int	export_add(char **input)
// {
// 	char		**res;
// 	static char	equal[2] = {'=', '\0'};
// 	int			i;
// 	t_env		*tmp;

// 	while (tmp && tmp->next && ++i)
// 		tmp = tmp->next;
// 	(tmp && i++);
// 	res = (char **)ft_calloc(sizeof(char *), i + 1);
// 	if (!res)
// 		return (NULL);
// 	i = -1;
// 	while (tmp && ++i >= 0)
// 	{
// 		res[i] = ft_strjoin(tmp->key, equal);
// 		if (!res[i])
// 			return (ft_free(res, 1));
// 		res[i] = ft_malloc_strjoin(res[i], tmp->value);
// 		if (!res[i])
// 			return (ft_free(res, 1));
// 		tmp = tmp->prev;
// 	}
// 	return (res);
// }

int	check_export(char *key, char	*value)
{
	int	i;

	i = 0;
	if (ft_isdigit(key[0]))
	{
		if (ft_printf(2, "Minishell: export: `%s=%s': \
		not a valid identifier\n", key, value) == -1)
			return (0);
	}
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			if (ft_printf(2, "Minishell: export: `%s=%s': \
			not a valid identifier\n", key, value) == -1)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_unset(char *node)
{
	int	i;

	i = 0;
	if (ft_isdigit(node[0]))
	{
		if (ft_printf(2, "Minishell: unset: `%s': \
		not a valid identifier\n", node) == -1)
			return (0);
	}
	while (node[i])
	{
		if (!ft_isalnum(node[i]) && node[i] != '_')
		{
			if (ft_printf(2, "Minishell: unset: `%s': \
			not a valid identifier\n", node) == -1)
				return (0);
		}
		i++;
	}
	return (1);
}
