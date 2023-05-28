/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:10:43 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/27 17:58:51 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

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

char	*ft_strip(char *str)
{
	char	*new;
	t_kof	fok;
	int		i[4];

	((1 && !(i[L] = 0)) && (i[I] = -1) && init_kof(&fok));
	while (str[++i[I]])
	{
		(check_qp(&fok, str[i[I]]) && (i[F] = 0));
		((fok.sq < 0 && fok.dq < 0) && str[i[I]] == ' ' && (i[F] = 1));
		while (i[F] && str[i[I] + 1] && str[i[I] + 1] == ' ')
			i[I]++;
		(((!((i[L] == 0 || !str[i[I] + 1]) && i[F]) && (i[L]++)) || 1));
	}
	new = ft_calloc(sizeof(char), (i[3] = i[L]) + init_kof(&fok));
	while (new && --i[I] >= 0)
	{
		(check_qp(&fok, str[i[I]]) && (i[F] = 0));
		((fok.sq < 0 && fok.dq < 0) && str[i[I]] == ' ' && (i[F] = 1));
		while (i[F] && i[I] >= 0 && str[i[I]] == ' ')
			i[I]--;
		(((i[F] && i[L] != i[3] && i[L] > 1 && (new[--i[L]] = ' ')) || 1) \
			&& i[L] > 0 && (new[--i[L]] = str[i[I]]));
	}
	return (new);
}

void	env_set_value(t_env **list, char *name, char *value)
{
	t_env	*env;
	char	**input;

	input = calloc(sizeof(char *), 3);
	input[0] = name;
	input[1] = value;
	if (!list || !name || !value || !*list)
		return ;
	env = env_search(list, name);
	if (env == NULL)
		export_add(input);
	else
	{
		free (env->value);
		env->value = ft_strdup(value);
	}
}

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

	tmp = ft_strdup(key);
	tmp2 = ft_strdup(value);
	env = node_create(tmp, tmp2);
	if (!env)
		return ((clean_env(&env, 1) && ft_free(&tmp, 2)));
	addfront_env(&g_msh.env, env);
	return (0);
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
