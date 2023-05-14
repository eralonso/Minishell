/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:00:02 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/14 18:39:35 by eralonso         ###   ########.fr       */
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

# define IN		(int)0
# define OUT	(int)1

# define I		(int)0
# define L		(int)1
# define F		(int)2

typedef struct s_redirect	t_redirect;
typedef struct s_cmd		t_cmd;
typedef struct s_kof		t_kof;
typedef struct s_block		t_block;
typedef struct s_env		t_env;
typedef struct s_msh		t_msh;

t_msh						g_msh;

struct s_redirect
{
	char	*in;
	char	*out;
	int		fd[2];
	int		tmp_fd[2];
};

struct s_cmd
{
	char			*pre_cmd;
	char			*path_cmd;
	char			**cmd_args;
	t_redirect		*redirect;
	t_cmd			*next;
};

struct s_block
{
	char	*line;
	int		lvl;
	char	sep;
	int		ret;
	t_cmd	*cmd;
	t_block	*child;
	t_block	*next;
};

struct s_kof
{
	int		op;
	int		cp;
	int		sq;
	int		dq;
	int		and;
	int		or;
};

struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
};

struct s_msh
{
	t_env	*env;
	t_block	*block;
	int		err;
};

char	**list_to_array(t_env **m_env);

t_env	*node_create(char *key, char *value);
void	addfront_env(t_env **msh_env, t_env *tmp);
void	ft_env(char **env);

int		check_qp(t_kof *fok, char c);
int		init_kof(t_kof *fok);
char	*ft_strip(char *str);


int		validate_input(char *input);
int		check_syntax(char *input);


int		make_blocks(char *str);
t_block	*create_block(char *str, int size, int lvl, char sep);
t_block	*generate_block(char *str, int lvl);
int		check_blocks(t_block *block);

int		ft_echo(char **input);
int		ft_echo_n(char **input);

#endif