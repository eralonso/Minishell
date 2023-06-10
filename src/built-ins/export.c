/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:01:58 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/10 16:12:59 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	exec_export(char **nodes)
{
	if (!nodes)
	{
		if (print_export())
			return (1);
	}
	else
		return (export_add(nodes));
	return (0);
}

int	print_export(void)
{
	char	**tmp;
	int		i;
	int		pos;

	i = -1;
	tmp = sort_env(list_to_array(&g_msh.env));
	if (!tmp)
		return (1);
	while (tmp[++i])
	{
		pos = ft_strchri(tmp[i], '=');
		tmp[i][pos] = '\0';
		ft_printf(1, "declare -x %s=\"%s\"\n", tmp[i], &tmp[i][pos + 1]);
		tmp[i][pos] = '=';
	}
	ft_free(tmp, 1);
	return (0);
}

int	export_add(char **input)
{
	char	*res[2];
	int		j;
	int		k;
	int		i;
	t_env	*tmp;

	j = -1;
	i = 0;
	while (++j < ft_matrixlen(input))
	{
		k = ft_strchri(input[i], '=');
		res[0] = ft_substr(input[j], 0, k);
		if (!res[0])
			clean_env(&g_msh.env, 0);
		res[1] = ft_substr(input[i], k + 1, ft_strlen(input[i]) - (k + 1));
		if (!res[1])
			clean_env(&g_msh.env, ft_free(&res[0], 2) == NULL);
		tmp = node_create(res[0], res[1]);
		if (!tmp || !check_export(res[0], res[1]))
			clean_env(&g_msh.env, !ft_free(&res[0], 2) | !ft_free(&res[1], 2));
		addfront_env(&g_msh.env, tmp);
		i++;
	}
	return (0);
}

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
