/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/18 16:53:46 by eralonso         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) av;
	if (ac > 1)
		exit(1);
	ft_env(env);
	set_null_node("OLDPWD", &g_msh.env);
	g_msh.err = 0;
	while (42)
	{
		g_msh.ctrl_c = 0;
		init_signals(NORM);
		do_sigign(SIGQUIT);
		line = readline("PESH + 🐚 > ");
		do_sigign(SIGINT);
		if (!line)
		{
			printf("exit");
			return (0);
		}
		if (*line && start(line))
			printf("ERROR\n\tg_msh.err: %i\n", g_msh.err);
	}
	return (0);
}
