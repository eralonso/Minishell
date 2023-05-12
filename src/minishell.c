/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/12 14:22:09 by eralonso         ###   ########.fr       */
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
		// printf("father: %s\n", g_msh.block->line);
		// printf("first child: %s\n", g_msh.block->child->line);
		// printf("next first child: %s\n", g_msh.block->child->next->line);
		// printf("next first child child: %s\n", g_msh.block->child->next->child->line);
		// printf("next first child child child: %s\n", g_msh.block->child->next->child->child->line);
		// printf("next first child child child: %s\n", g_msh.block->child->next->child->child->child->next->line);
	}
	return (0);
}
