/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/09 15:33:42 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_env	*node_create(char *key,  char	*value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	addfront_env(t_env **msh_env, t_env *tmp)
{
	if (*msh_env)
	{
		tmp->next = *msh_env;
		(*msh_env)->prev = tmp;
	}
	*msh_env = tmp;
}

void	ft_env(char **env)
{
	char	**res;
	int		i;
	t_env	*tmp;

	i = -1;
	g_msh.env = NULL;
	while (env[++i])
	{
		res = ft_split(env[i], '=');
		if (!res)
			exit(1);// error_handler (NULL);
		tmp = node_create(res[0], res[1]);
		if (!tmp)
			exit(1);// error_handler (NULL);
		addfront_env(&g_msh.env, tmp);
		free(res);
	}
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	char	*line;
	
	if (ac > 1)
		exit(1);
	ft_env(env);
	while (42)
	{
		line = readline("PESH + 🐚 > ");
		if (!line)
			break ;
		else if (!*line)
			continue ;
	}
	return (0);
}
