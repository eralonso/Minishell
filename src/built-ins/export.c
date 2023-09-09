/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:01:58 by pramos-m          #+#    #+#             */
/*   Updated: 2023/09/09 16:29:50 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

static char	**export_split(char *str, int *id);
static int	export_new_add(char **pair, int id, char *str);
static int	export_identifier(char *str, int *pos);

int	exec_export(char **nodes)
{
	int		i;
	int		status;
	int		id;
	char	**pair;

	i = -1;
	status = 0;
	if (nodes[0])
	{
		while (nodes[++i])
		{
			pair = export_split(nodes[i], &id);
			if (!pair && id != INVALID)
				return (1);
			else if (id != INVALID && export_new_add(pair, id, nodes[i]))
				return (1);
		}
		return (status);
	}
	else if (print_export())
		return (1);
	return (0);
}

static int	export_identifier(char *str, int *pos)
{
	int	sep_pos[2];

	sep_pos[0] = ft_strnstri(str, "+=", 0xFFFFFF);
	sep_pos[1] = ft_strchri(str, '=');
	*pos = sep_pos[0];
	if (sep_pos[0] == 0 || sep_pos[1] == 0)
		return (INVALID);
	else if (sep_pos[0] + sep_pos[1] == -2)
	{
		*pos = ft_strlen(str);
		return (NONE);
	}
	else if (sep_pos[0] > 0 && sep_pos[0] < sep_pos[1])
		return (ADD);
	*pos = sep_pos[1];
	return (EQUAL);
}

static char	**export_split(char *str, int *id)
{
	char	**pair;
	int		pos;

	*id = export_identifier(str, &pos);
	if (*id == INVALID)
		return (msg_error("export", str, NVI, 2), NULL);
	pair = ft_calloc(sizeof(char *), 3);
	if (!pair)
		return (NULL);
	pair[0] = ft_substr(str, 0, pos);
	if (!pair[0])
		return (ft_free(pair, 1));
	if (*id != NONE)
	{
		pair[1] = ft_substr(str, pos + *id, 0xFFFFFF);
		if (!pair[1])
			return (ft_free(pair, 1));
	}
	return (pair);
}

static int	export_new_add(char **pair, int id, char *str)
{
	int	status;

	if (!check_export(pair[0], str))
	{
		ft_free(pair, 1);
		return (0);
	}
	status = node_update(pair[0], pair[1], id);
	ft_free(pair, 1);
	return (status);
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
		(pos > 0 && (tmp[i][pos] = '\0'));
		if (pos > 0)
			ft_printf(1, "declare -x %s=\"%s\"\n", tmp[i], &tmp[i][pos + 1]);
		else
			ft_printf(1, "declare -x %s\n", tmp[i]);
		(pos > 0 && (tmp[i][pos] = '='));
	}
	ft_free(tmp, 1);
	return (0);
}
