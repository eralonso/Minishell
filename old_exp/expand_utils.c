/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:14:45 by pramos-m          #+#    #+#             */
/*   Updated: 2023/06/08 18:55:43 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	var_size(char *str)
{
	int	i;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[1] == '?')
		i++;
	if (i == 1)
		return (0);
	return (i);
}

int	env_var_count(char *str)
{
	int		i;
	int		count;
	t_kof	fok;

	i = -1;
	count = 0;
	init_kof(&fok);
	while (str[++i] != '\0')
	{
		check_qp(&fok, str[i]);
		if (fok.sq < 0 && str[i] == '$' \
		&& (ft_isalnum(str[i + 1]) || ft_strchr("_?", str[i + 1])))
			count++;
	}
	return (count);
}

int	var_total_size(char *str, char **vars)
{
	int		i;
	int		count;
	t_kof	fok;

	init_kof(&fok);
	i = 0;
	count = ft_strlen(str);
	while (str[i])
	{
		check_qp(&fok, str[i]);
		if (fok.sq < 0 && str[i] == '$')
			count -= var_size(&str[i]);
		i++;
	}
	i = 0;
	while (vars[i])
	{
		count += ft_strlen(vars[i]);
		i++;
	}
	return (count);
}

char	*var_line(char *str, char **vars, int size)
{
	char	*line;
	t_kof	fok;
	int		i;
	int		j;
	int		k;

	(0 || (i = 0) || (j = 0) || (k = 0));
	init_kof(&fok);
	line = ft_calloc(sizeof(char), size + 1);
	if (!line)
		return (NULL);
	while (str[i])
	{
		check_qp(&fok, str[i]);
		if (fok.sq < 0 && str[i] == '$' && (ft_isalnum(str[i + 1]) \
		|| ft_strchr("_?", str[i + 1])))
		{
			ft_strcat(line, vars[k]);
			i += var_size(&str[i]);
			j += ft_strlen(vars[k++]);
		}
		else
			line[j++] = str[i++];
	}
	return (line);
}
