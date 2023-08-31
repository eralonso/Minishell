/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:20:26 by pramos-m          #+#    #+#             */
/*   Updated: 2023/08/31 13:30:39 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

int	init_signals(int mode)
{
	struct sigaction	signal;

	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (mode == NORM)
		signal.sa_sigaction = norm_handler;
	else if (mode == N_INTERACT)
		signal.sa_sigaction = ninter_handler;
	else if (mode == HEREDOC)
		signal.sa_sigaction = heredoc_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	return (0);
}

void	do_sigign(int signum)
{
	struct sigaction	signal;

	signal.sa_handler = SIG_IGN;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(signum, &signal, NULL) < 0)
		exit (1);
}

void	norm_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		ft_printf(1, "\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_msh.err = 1;
	}
	return ;
}

void	heredoc_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		g_msh.err = 1;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		ft_printf(1, "\n");
		exit(1);
	}
	return ;
}

void	ninter_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		g_msh.err = 130;
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		g_msh.err = 131;
		exit(130);
	}
	return ;
}
