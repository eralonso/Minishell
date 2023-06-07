/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:24:05 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/07 18:49:02 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	are_expansions(char *line)
{
	t_kof	fok;
	int		i;

	if (!line)
		return (0);
	i = -1;
	init_kof(&fok);
	while (line[++i])
	{
		check_qp(&fok, line[i]);
		if (fok.sq < 0 && line[i] == '$')
			return (1);
		if (fok.sq < 0 && fok.dq < 0 && line[i] == '*' \
		&& !ft_strchr(line, '/') && wdc_able(line))
			return (1);
	}
	return (0);
}

void	expand(t_token **tk)
{
	int		f_pipe;
	t_token	*tmp;
	int		paren;

	(0 || (f_pipe = 0) || (paren = 0) || (tmp = *tk));
	while (tmp && tmp->type != EOCL)
	{
		if (tmp->type == ARG && are_extensions(tmp->line))
		{
			tmp->line = expand_line(tmp->line, f_pipe);
			if (!tmp->line)
				return (NULL);
		}
		(0 || (tmp->type = OP && paren++) || (tmp->type == CP && paren--));
		if (!paren && tmp->type == PIPE)
			f_pipe = 1;
		tmp = tmp->next;
	}
}
