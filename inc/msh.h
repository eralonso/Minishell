/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:00:02 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/31 16:55:22 by pramos-m         ###   ########.fr       */
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
# include	<sys/stat.h>

# define IN		(int)0
# define OUT	(int)1

# define NORM		(int)1
# define HEARDOC	(int)2
# define N_INTERACT	(int)2

# define I		(int)0
# define L		(int)1
# define F		(int)2

# define ARG	(int)0
# define PIPE	(int)1
# define RDI	(int)2
# define RDO	(int)3
# define RDHD	(int)4
# define RDAP	(int)5
# define AND	(int)6
# define OR		(int)7
# define OP		(int)8
# define CP		(int)9

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
	t_token	*next;
	int		sub_sh;
	int		sub_shlvl;
};

struct s_block
{
	t_token	*tk;
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

//Debugging Tools
void	print_cmd(t_cmd *cmd, int lvl);

//Enviroment: Create
t_env	*node_create(char *key, char *value);
void	addfront_env(t_env **msh_env, t_env *tmp);
void	ft_env(char **env);

// Enviroment: Utils
char	**list_to_array(t_env **m_env);
t_env	*env_search(t_env **env, char *key);
void	env_unset_node(t_env *env, char	*node);
int		exec_unset(t_env **env, char *node);
char	**sort_env(char **env);
void	print_export(void);
int		clean_env(t_env **list, int ret);
void	env_set_value(t_env **list, char *name, char *value);

// Validate
int		validate_input(char *input);
int		check_syntax(char *input);
int		check_paren(char *str);

// Validate: Utils
int		check_qp(t_kof *fok, char c);
int		check_bb(char *str, int i);
int		init_kof(t_kof *fok);
char	*ft_strip(char *str);

// Blocks Management
int		make_blocks(char *str);
t_block	*create_block(char *str, int size, int lvl, char sep);
t_block	*generate_block(char *str, int lvl);
int		check_blocks(t_block *block);

// CMD: Create
int		build_cmd(t_block *block);
t_cmd	*line_cmd(char *str);
t_cmd	*create_cmd(char *str);

// CMD: Utils
char	**split_cmd(char *str);
void	addback_cmd(t_cmd **cmd, t_cmd *new);
int		cmd_lstclear(t_cmd **cmd, int ret);

// Builtins
int		ft_echo(char **input);
int		ft_echo_n(char **input);
int		ft_pwd(char *input);
void	print_env(t_env **env);
int		print_one_env(char *input);
int		export_add(char **input);
int		exec_export(char **nodes);
int		exec_exit(char **exit);
int		validate_args(char **node, int *value);
int		is_valid_num(char *data);
int		print_exit_error(char *data);
int		exec_cd(char **input);
char	*env_node_value(t_env *env, char *key);
int		create_add_node(char *key, char *value);
int		get_cd_dir(char **input, char **pwd);
int		exec_changed(char *pwd, char *old_pwd);
int		env_pwd_change(t_env **env, char *pwd, char *old_pwd);
void	set_null_node(char *key, t_env **env);

//Wildcard
char	**get_wildcard(void);
int		ft_count_dir(DIR *dir);

//Signals
int		init_signals(int mode);
void	norm_handler(int sig, siginfo_t *data, void *non_used_data);
void	ninter_handler(int sig, siginfo_t *data, void *non_used_data);
void	do_sigign(int signum);
void eof_handler(int signum);

#endif