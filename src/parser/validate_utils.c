/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:25 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/16 15:24:40 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	check_qp(t_kof *fok, char c)
{
	((fok->sq < 0) && (c == '\"') && (fok->dq *= -1));
	((fok->dq < 0) && (c == '\'') && (fok->sq *= -1));
	((fok->sq < 0 && fok->dq < 0) && (c == '(') && (fok->op++));
	(((fok->sq < 0 && fok->dq < 0) && c == ')') && (fok->cp++));
	return (1);
}

int	check_bb(char *str, int i)
{
	if (i > 0)
	{
		(ft_isspace(str[i - 1]) && (i--));
		if (i - 1 >= 0 && !ft_strchr("&|(", str[i - 1]))
			return (1);
	}
	return (0);
}
