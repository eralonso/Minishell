/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:26:22 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/21 11:49:44 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	rmqt_size(char *str)
{
	int		len;
	int		i;
	t_kof	fok;

	i = 0;
	len = 0;
	init_kof(&fok);
	while (str[i])
	{
		check_qp(&fok, str[i]);
		if (!(fok.sq < 0 && str[i] == '\"') \
		&& !(fok.dq < 0 && str[i] == '\''))
			len++;
		i++;
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	t_kof	fok;
	char	*clean;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	clean = ft_calloc(sizeof(char), rmqt_size(str) + 1);
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	init_kof(&fok);
	while (str[i])
	{
		check_qp(&fok, str[i]);
		if (!(fok.sq < 0 && str[i] == '\"') \
		&& !(fok.dq < 0 && str[i] == '\''))
			clean[j++] = str[i];
		i++;
	}
	return (clean);
}

int	node_update(char *key, char *value)
{
	t_env	*tmp;

	tmp = env_search(&g_msh.env, key);
	if (!tmp)
	{
		if (create_add_node(key, value))
			return (1);
		return (0);
	}
	ft_free(&tmp->value, 2);
	if (value)
	{
		tmp->value = ft_strdup(value);
		if (!tmp->value)
			return (1);
	}
	return (0);
}

void	msh_exit(int status)
{
	ctrl_c(SET);
	g_msh.err = status;
	st_clean(&g_msh.stair);
	clean_env(&g_msh.env, 0);
	exit(status);
}
