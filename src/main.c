/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/10 18:05:28 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	print_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	(void) av;
	char	**input = (char **)malloc(sizeof(char *) * 2);
	if (ac > 1)
		exit(1);
	ft_env(env);
	set_null_node("OLDPWD", &g_msh.env);
	init_signals(NORM);
	g_msh.err = 0;
	g_msh.wild = get_wildcard(CURRENT_DIR);
	while (42)
	{
		do_sigign(SIGQUIT);
		line = readline("PESH + 🐚 > ");
		do_sigign(SIGINT);
		if (!line)
		{
			printf("exit");
			return (0);
		}
		input[0] = line;
		input[1] = NULL;
		exec_cd(input);
		print_env(&g_msh.env);
		add_history(line);
		if (*line && validate_input(line))
			printf("ERROR\nerr: %i\n", g_msh.err);
	}
	return (0);
}
