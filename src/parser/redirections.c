/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:45:30 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/22 19:39:26 by eralonso         ###   ########.fr       */
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
	{
		tk_clean(&redirect[i].file_tk, NEXT);
		free(redirect[i].file);
	}
	free(redirect);
	return (NULL);
}

void	do_here_doc(char *limiter, int fd_here_doc[2])
{
	char	*str;

	init_signals(HEREDOC);
	do_sigign(SIGQUIT);
	str = readline("> ");
	while (str && ft_strncmp(str, limiter, 0xFFFF))
	{
		if (ft_printf(fd_here_doc[1], "%s\n", str) == -1)
		{
			ft_free(&str, 2);
			ft_close(&fd_here_doc[0]);
			ft_close(&fd_here_doc[1]);
			exit(2);
		}
		ft_free(&str, 2);
		do_sigign(SIGQUIT);
		str = readline("> ");
	}
	ft_free(&str, 2);
	if (ft_close(&fd_here_doc[1]) == -1 || ft_close(&fd_here_doc[0]) == -1)
		exit(2);
	exit(0);
}

int	create_hdoc(char *limiter)
{
	pid_t	hd;
	int		status;
	int		fd_here_doc[2];
	int		err;

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
	if (WIFEXITED(status))
	{
		err = WEXITSTATUS(status);
		if (err == 1)
			g_msh.ctrl_c = 1;
		else if (err == 2)
			return (-1);
	}
	return (fd_here_doc[0]);
}

static int	check_redirect(t_token *tmp, t_redirect *redir, int i)
{
	int		ret;

	ret = 0;
	if (tk_isredirection(tmp))
	{
		ret = 1;
		redir[i].type = tmp->type;
		redir[i].file_tk = tk_copy(tmp->next);
		if (!redir[i].file_tk)
			return (-1);
	}
	if (tk_isredirection(tmp) == 2)
	{
		redir[i].file = remove_quotes(redir[i].file_tk->line);
		if (!redir[i].file)
			return (-1);
		redir[i].fd[IN] = create_hdoc(redir[i].file);
		if (redir[i].fd[IN] <= 0)
			return (-1);
	}
	return (ret);
}

t_redirect	*create_redirect(t_token **tk, int size, int skip_p)
{
	t_redirect	*redir;
	t_token		*tmp;
	int			paren;
	int			i;
	int			ret;

	if (!tk || !*tk || (*tk)->type == EOCL)
		return (NULL);
	(1 && (tmp = *tk) && ((paren = 0) || (i = 0)));
	redir = (t_redirect *)ft_calloc(sizeof(t_redirect), size);
	if (!redir)
		return (NULL);
	while (!g_msh.ctrl_c && tmp && tmp->next && tmp->type != EOCL)
	{
		((tmp->type == OP && (paren++)) || (tmp->type == CP && (paren--)));
		(0 || (ret = 0) || (paren *= skip_p));
		if (!paren && tk_isredirection(tmp))
			ret = check_redirect(tmp, redir, i);
		if (ret == -1)
			return (rd_clean(redir, size));
		(ret == 1 && (tmp = tmp->next) && (i++));
		tmp = tmp->next;
	}
	return (redir);
}
