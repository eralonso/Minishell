/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:42:55 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/25 17:31:12 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

char	**sort_env(char **env)
{
	int		size;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	size = ft_matrixlen(env);
    while (i < size - 1) {
        j = 0;
        while (j < size - i - 1) {
            if ((int)env[j][0] > (int)env[j + 1][0]) {
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