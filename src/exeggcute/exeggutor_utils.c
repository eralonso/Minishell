/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:21:50 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/18 12:56:16 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	redir_std(int dst[2], const int src[2])
{
	int	err;
	int	tmp;

	err = 0;
	tmp = dup2(dst[0], src[0]);
	if (tmp < 0)
		err = tmp;
	tmp = dup2(dst[1], src[1]);
	if (tmp < 0)
		err = tmp;
	tmp = ft_close(&dst[0]);
	if (tmp < 0)
		err = tmp;
	tmp = ft_close(&dst[1]);
	if (tmp < 0)
		err = tmp;
	return (err);
}
