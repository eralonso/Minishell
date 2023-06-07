/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:42:55 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/07 13:36:30 by pramos-m         ###   ########.fr       */
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
