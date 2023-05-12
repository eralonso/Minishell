/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/12 11:13:12 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) av;
	if (ac > 1)
		exit(1);
	ft_env(env);
	while (42)
	{
		line = readline("PESH + 🐚 > ");
		if (!line)
			break ;
		if (validate_input(line))
			break ;
		char **memuero = ft_split(line, ' ');
			ft_echo(memuero);
	}
	return (0);
}
