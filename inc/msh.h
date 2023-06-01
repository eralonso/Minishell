/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:00:02 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/01 17:39:24 by eralonso         ###   ########.fr       */
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
# include	<libft.h>
# include	<ft_printf.h>

# define IN		(int)0
# define OUT	(int)1

# define I		(int)0
# define L		(int)1
# define F		(int)2

# define TK		(int)0
# define BK		(int)1

# define EOCL	(int)0
# define RDHD	(int)1
# define PIPE	(int)2
# define RDAP	(int)3
# define RDI	(int)4
# define AND	(int)5
# define RDO	(int)6
# define OR		(int)7
# define OP		(int)8
# define ARG	(int)9
# define CP		(int)10

typedef struct s_redirect	t_redirect;
typedef struct s_cmd		t_cmd;
typedef struct s_kof		t_kof;
typedef struct s_token		t_token;
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

struct s_token
{
	int		type;
	char	*line;
	int		sub_sh;
	int		sub_shlvl;
	t_token	*next;
	t_token	*prev;
};

struct s_block
{
	t_token	*tk;
	t_block	*next;
	t_block	*child;
	int		sep;
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

//Debugging Tools
void	print_cmd(t_cmd *cmd, int lvl);

//Parser: Tokens: Synthesize
t_token	*tokenizer(char *str);
t_token	*tk_analyzer(char *str, int *i, int *shlvl);

//Parser: Tokens: Utils
void	*tk_clean(t_token **tk);
void	tk_bk_addback(void **tk, void *new, int type);
t_token	*tk_create(char *str, int type, int size, int subsh_lvl);
int		check_tokens(t_token **tk);

//Enviroment: Create
t_env	*node_create(char *key, char *value);
void	addfront_env(t_env **msh_env, t_env *tmp);
void	ft_env(char **env);

// Enviroment: Utils
char	**list_to_array(t_env **m_env);
t_env	*env_search(t_env *list, char *key);
void	env_unset_node(t_env *env, char	*node);
int		exec_unset(t_env **env, char *node);
char	**sort_env(char **env);
void	print_export(void);

// Validate
int		validate_input(char *input);
int		check_syntax(char *input);
int		check_paren(char *str);

// Validate: Utils
int		check_qp(t_kof *fok, char c);
int		check_bb(char *str, int i);
int		init_kof(t_kof *fok);
char	*ft_strip(char *str);

// Builtins
int		ft_echo(char **input);
int		ft_echo_n(char **input);
int		ft_pwd(char *input);
void	print_env(t_env *env);
int		print_one_env(char *input);

#endif