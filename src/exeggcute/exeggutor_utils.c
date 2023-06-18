/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:21:50 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/18 16:20:18 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	exec_clean(int tmp_fd[2], const int std_fd[2], pid_t *pids, int size)
{
	redir_std(tmp_fd, std_fd);
	kill_childs(pids, size);
	free(pids);
	return (1);
}

int	redir_std(int dst[2], const int src[2])
{
	int	err;
	int	tmp;

	err = 0;
	tmp = dup2(dst[IN], src[IN]);
	if (tmp < 0)
		err = tmp;
	tmp = dup2(dst[OUT], src[OUT]);
	if (tmp < 0)
		err = tmp;
	if (dst[IN] != src[IN])
	{
		tmp = ft_close(&dst[IN]);
		if (tmp < 0)
			err = tmp;
	}
	if (src[OUT] != dst[OUT])
	{
		tmp = ft_close(&dst[OUT]);
		if (tmp < 0)
			err = tmp;
	}
	return (err);
}
