/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:52:36 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 16:44:20 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	redirect_parser(t_redirect *redir, int size)
{
	int		i;
	t_list	*args;

	i = -1;
	while (++i < size)
	{
		if (redir[i].type != RDHD)
		{
			args = real_list(&redir[i].file_tk);
			if (!args)
				return (1);
			if (args->next)
			{
				redir[i].warn = 1;
				ft_lstclear(&args, free);
			}
			else
			{
				redir[i].file = args->content;
				free(args);
			}
		}
	}
	return (0);
}

int	ft_access(char *file, int mode)
{
	int	ret;

	ret = 0;
	if (mode == IN)
	{
		if (access(file, F_OK))
			(1 && (ret = -1) && msg_error(file, NFD, NULL, 0));
		if (!ret && access(file, R_OK))
			(1 && (ret = -1) && msg_error(file, PERM, NULL, 0));
	}
	if (mode == OUT)
	{
		if (!access(file, F_OK) && access(file, W_OK))
			(1 && (ret = -1) && msg_error(file, PERM, NULL, 0));
		if (ft_strchr(file, '/') && access(file, F_OK))
			(1 && (ret = -1) && msg_error(file, NFD, NULL, 0));
	}
	return (ret);
}

int	check_file(char *file, int type, int mode)
{
	int	fd;
	int	flag;

	fd = -1;
	if (ft_access(file, mode))
		return (-1);
	if (mode == IN)
		fd = open(file, O_RDONLY);
	else if (mode == OUT)
	{
		flag = O_TRUNC;
		if (type == RDAP)
			flag = O_APPEND;
		fd = open(file, O_WRONLY | O_CREAT | flag, 0666);
	}
	if (fd < 0)
		msg_error("open: Error trying open file", file, NULL, 2);
	return (fd);
}

int	last_redirect(t_redirect *redir, int size, int last_fd[2])
{
	int	mode;
	int	i;

	if (!redir || size < 0)
		return (0);
	i = 0;
	while (i < size)
	{
		if (redir[i].warn)
			msg_error("*", "ambiguos redirect", NULL, 0);
		if (redir[i].warn)
			return (-1);
		mode = OUT;
		if (redir[i].type == RDI || redir[i].type == RDHD)
			mode = IN;
		if (redir[i].type != RDHD)
			redir[i].fd[mode] = check_file(redir[i].file, redir[i].type, mode);
		if (last_fd[mode] > 1 && last_fd[mode] != g_msh.std_fd[mode])
			ft_close(&last_fd[mode]);
		last_fd[mode] = redir[i].fd[mode];
		if (last_fd[mode] < 0)
			return (last_fd[mode]);
		i++;
	}
	return (0);
}

int	redirect_node(t_lstt *node, int tmp_fd[2])
{
	int			last_fd[2];
	const int	std_fd[2] = {0, 1};
	int			err;

	last_fd[IN] = tmp_fd[IN];
	last_fd[OUT] = tmp_fd[OUT];
	if (node->prev)
		last_fd[IN] = node->prev->fd[IN];
	if (node->next)
		last_fd[OUT] = node->fd[OUT];
	if (node->redir_size)
	{
		err = last_redirect(node->redirect, node->redir_size, last_fd);
		if (err)
			return (1);
	}
	if (redir_std(last_fd, std_fd, 0))
		return (1);
	return (0);
}
