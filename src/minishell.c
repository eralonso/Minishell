/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/05 16:42:26 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	char	*line;
	
	while (42)
	{
		line = readline("❤️> ");
		if (!line || !*line)
			break ;
		printf("line: %s\n", line);
	}
	return (0);
}
