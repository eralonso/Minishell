/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstt_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:44:41 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/03 19:12:05 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	*rd_clean(t_redirect *redirect, int size)
{
	int	i;

	if (!redirect)
		return (NULL);
	i = -1;
	while (++i < size)
		free(redirect[i].file);
	free(redirect);
	return (NULL);
}

void	do_here_doc(char *limiter, int fd_here_doc[2])
{
	char	*str;

	if (ft_printf(1, "> ") == -1)
		exit(ft_close(&fd_here_doc[0]) || ft_close(&fd_here_doc[0]) || 1);
	str = get_next_line(0);
	while (str && ft_strncmp(str, limiter, 0xFFFFFFFF))
	{
		if (ft_printf(fd_here_doc[1], str) == -1)
			exit((ft_free(&str, 2) || ft_close(&fd_here_doc[0]) \
					|| ft_close(&fd_here_doc[0])) || 1);
		ft_free(&str, 2);
		if (ft_printf(1, "> ") == -1)
			exit(ft_close(&fd_here_doc[0]) || ft_close(&fd_here_doc[0]) || 1);
		str = get_next_line(0);
	}
	ft_free(&str, 2);
	if (ft_close(&fd_here_doc[1]) == -1)
		exit(1);
	exit(0);
}

int	create_hdoc(char *limiter)
{
	pid_t	hd;
	int		status;
	int		fd_here_doc[2];

	if (pipe(fd_here_doc) == -1)
		return (-1);
	hd = fork();
	if (hd == -1)
		return (-1);
	if (hd == 0)
		do_here_doc(limiter, fd_here_doc);
	if (ft_close(&fd_here_doc[1]) == -1)
		return (kill(hd, SIGTERM));
	if (waitpid(hd, &status, 0) == -1)
		return (ft_close(&fd_here_doc[0]));
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (-1);
	return (fd_here_doc[0]);
}

t_redirect	*lstt_redirect(t_token **tk, int skip_p)
{
	t_redirect	*redir;
	t_token		*tmp;
	int			paren;
	int			i;

	if (!tk || !*tk || (*tk)->type == EOCL)
		return (NULL);
	(1 && (tmp = *tk) && ((paren = 0) || (i = 0)));
	redir = (t_redirect *)ft_calloc(sizeof(t_redirect), \
		tk_tkcounter(tk, RD, EOCL, ON) + 1);
	if (!redir)
		return (NULL);
	while (tmp && tmp->next && tmp->type != EOCL)
	{
		((tmp->type == OP && (paren++)) || (tmp->type == CP && (paren--)));
		paren *= skip_p;
		if ((tmp->type == RDI || tmp->type == RDO || tmp->type == RDAP \
			|| tmp->type == RDHD) && paren == 0)
		{
			redir[i].type = tmp->type;
			redir[i].file = ft_strdup(tmp->next->line);
			if (!redir[i++].file)
				return (rd_clean(redir, tk_tkcounter(tk, RD, EOCL, ON)));
			tmp = tmp->next;
		}
		if (tmp->prev && tmp->prev->type == RDHD && paren == 0)
		{
			redir[i].fd[0] = create_hdoc(redir[i].file);
			if (redir[i].fd[0] <= 0)
				return (rd_clean(redir, tk_tkcounter(tk, RD, EOCL, ON)));
		}
		tmp = tmp->next;
	}	
	return (redir);
}

void	lstt_addback(t_lstt **list, t_lstt *bottom)
{
	t_lstt	*tmp;

	if (!list)
		return ;
	if (!*list)
	{
		*list = bottom;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = bottom;
}
