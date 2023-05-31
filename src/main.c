/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/31 17:59:17 by pramos-m         ###   ########.fr       */
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
	char	**input;

	(void) av;
	if (ac > 1)
		exit(1);
	ft_env(env);
	set_null_node("OLDPWD", &g_msh.env);
	while (42)
	{
		init_signals(NORM);
		do_sigign(SIGQUIT);
		line = readline("PESH + 🐚 > ");
		do_sigign(SIGINT);
		if (!line)
		{
			printf("exit");
			return (0);
		}
		input = calloc(sizeof(char *), 3);
		input = get_wildcard();
		if (*line && validate_input(line))
			printf("ERROR\nerr: %i\n", g_msh.err);
		free(input);
		g_msh.err = 0;
	}
	return (0);
}

// printf("first child line: :%s:\n", g_msh.block->child->line);
// printf("first child line: :%s:\n", g_msh.block->child->next->child->
// child->child->line);
// printf("first child line: :%s:\n", g_msh.block->child->next->child->
// child->child->next->line);
// printf("first child line: :%s:\n", g_msh.block->child->next->child->
// child->next->line);
// printf("first child line: :%s:\n", g_msh.block->child->next->child->
// next->line);
// printf("first child line: :%s:\n", g_msh.block->child->next->next->line);
// printf("first child: :%s:\n", g_msh.block->child->line);
// printf("next first child: :%s:\n", g_msh.block->child->next->line);
// printf("next first child child: :%s:\n", g_msh.block->child->next->
// child->line);
// printf("next first child child child: :%s:\n", g_msh.block->child->
// next->child->child->line);
// printf("next first child child child: :%s:\n", g_msh.block->child->
// next->child->child->child->next->line);
