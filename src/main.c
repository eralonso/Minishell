/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/23 15:30:42 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	print_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			if (printf("%s=%s\n", tmp->key, tmp->value) == -1)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ctrl_c(int mode)
{
	struct termios	tc;

	tcgetattr(g_msh.std_fd[IN], &tc);
	tc.c_lflag &= ~ECHOCTL;
	if (mode == SET)
		tc.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
}

void	restart_global(void)
{
	g_msh.ctrl_c = 0;
	g_msh.std_fd[IN] = 0;
	g_msh.std_fd[OUT] = 1;
}

void	set_up(char **env)
{
	g_msh.err = 0;
	restart_global();
	ft_env(env);
	set_null_node("OLDPWD", &g_msh.env);
	ctrl_c(UNSET);
}

int	main(int ac, char **av, char **env)
{
	char			*line;

	(void) av;
	if (ac > 1)
		exit(1);
	set_up(env);
	while (42)
	{
		restart_global();
		init_signals(NORM);
		do_sigign(SIGQUIT);
		line = readline("PESH + 🐚 > ");
		do_sigign(SIGINT);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_printf(2, "exit\n");
			ctrl_c(SET);
			return (clean_env(&g_msh.env, g_msh.err));
		}
		if (*line && start(line))
			printf("\nFatal Error\n\tg_msh.err: %i\n", g_msh.err);
	}
	return (0);
}
