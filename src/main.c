/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/06 17:53:19 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	print_env(t_env *env)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = list_to_array(&env);
	while (tmp[++i])
		printf("%s\n", tmp[i]);
}

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
		if (*line && validate_input(line))
			printf("ERROR\nerr: %i\n", g_msh.err);
		g_msh.err = 0;
	}
	return (0);
}
