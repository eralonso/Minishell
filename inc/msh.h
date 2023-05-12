/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:00:02 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/12 13:24:53 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include	<limits.h>
# include	<errno.h>
# include	<stdbool.h>
# include   <stdlib.h>
# include   <stdio.h>
# include   <unistd.h>
# include	<curses.h>
# include	<term.h>
# include	<tcl.h>
# include	<sys/wait.h>
# include	<sys/types.h>
# include	<dirent.h>
# include	<signal.h>
# include	<readline.h>
# include	<history.h>
# include	<ft_printf.h>

typedef struct s_block
{
	char			*line;
	int				lvl;
	struct	s_block	*child;
	struct	s_block	*next;
	int				ret;
	char			sep;
}				t_block;

typedef	struct s_kof
{
	int		op;
	int		cp;
	int		sq;
	int		dq;
	int		and;
	int		or;
}				t_kof;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct s_msh
{
	t_env	*env;
	t_block	*block;
	int		err;
}				t_msh;

t_msh	g_msh;

char	**list_to_array(t_env **m_env);
t_env	*node_create(char *key, char *value);
void	addfront_env(t_env **msh_env, t_env *tmp);
void	ft_env(char **env);
int		validate_input(char *input);
int		check_syntax(char *input, t_kof *fok);

int		make_blocks(char *str);
t_block	*create_block(char *str, int size, int lvl, char sep);
t_block	*find_block(char *str, int lvl);

int		ft_echo(char **input);
int		ft_echo_n(char **input);

#endif