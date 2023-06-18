/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:52:36 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/18 14:48:35 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	redirect_parser(t_redirect *redir, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		redir[i].file = subarg_expand(redir[i].file_tk);
		if (!redir[i].file)
			return (1);
	}
	return (0);
}

int	check_file(char *file, int type, int mode)
{
	int	fd;
	int	flag;

	fd = -1;
	if (mode == IN)
	{
		if (access(file, F_OK | R_OK))
			return (-1);
		fd = open(file, O_RDONLY);
	}
	else if (mode == OUT)
	{
		if (!access(file, F_OK) && access(file, W_OK))
			return (-1);
		flag = O_TRUNC;
		if (type == RDAP)
			flag = O_APPEND;
		fd = open(file, O_WRONLY | O_CREAT | flag, 0666);
	}
	if (fd < 0)
		return (-1);
	return (fd);
}

int	last_redirect(t_redirect *redir, int size, int last_fd[2])
{
	int	mode;
	int	i;

	if (!redir || size < 0)
		return (-1);
	i = 0;
	while (i < size)
	{
		mode = OUT;
		if (redir[i].type == RDI || redir[i].type == RDHD)
			mode = IN;
		if (redir[i].type != RDHD)
			redir[i].fd[mode] = check_file(redir[i].file, redir[i].type, mode);
		last_fd[mode] = redir[i].fd[mode];
		if (last_fd[mode] < 0)
			return (1);
		i++;
	}
	return (0);
}

int	redirect_node(t_lstt *node)
{
	int	last_fd[2];

	printf("aaa\n");
	if (last_redirect(node->redirect, node->redir_size, last_fd))
		return (1);
	printf("bbb\n");
	return (0);
}
