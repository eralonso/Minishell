/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:53:13 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/19 12:43:56 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

//Includes
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

//Defines
///Errors: Value
# define ERR_NODE	(int)-1

///FD
# define IN		(int)0
# define OUT	(int)1

///Parenthesis
# define OFF	(int)0
# define ON		(int)1

///Iterator, Len, Flag
# define I		(int)0
# define L		(int)1
# define F		(int)2

///Type of struct: TK == token, BK == Block
# define TK		(int)0
# define BK		(int)1

///Direction to clean
# define NEXT	(int)0
# define PREV	(int)1

///Signals modes
# define NORM		(int)1
# define HEREDOC	(int)2
# define N_INTERACT	(int)3

///Directory
# define CURRENT_DIR	(char *)"."

///Types of tokens: 
////EOCL == End Of Command Line, RDHD == ReDirection Here Doc '<<',
////PIPE == Pipe '|', RDAP == ReDirection APpend '>>',
////RDI == ReDirection Input '<', AND == And '&&', 
////RDO == ReDirection Output '>', OR == Or '||', 
////OP == Open Parenthesis '(', ARG == Argument == 
////Text {[A ... Z], [a ... z], [0 ... 9]}, CP == Close Parenthesis ')',
////LOGIC == LOGIC operator {&&, ||}, RD == ReDirections == {<, >, <<, >>}
# define EOCL		(int)0
# define RDHD		(int)1
# define PIPE		(int)2
# define RDAP		(int)3
# define RDI		(int)4
# define AND		(int)5
# define RDO		(int)6
# define OR			(int)7
# define OP			(int)8
# define ARG		(int)9
# define CP			(int)10
# define LOGIC		(int)11
# define RD			(int)12
# define LIMITER	(int)13

///Types of ARG: 
////TXT == Text {[a ... z], [A ... Z], [0 ... 9]}
////VAR == Enviroment variable '$', WILD == Wildcard '*'
# define TXT	(int)1
# define VAR	(int)2
# define WILD	(int)3

///Type of node: MAIN == First Step, CMD == CoMmanD, STAIR == subshell/stair
# define CMD	(int)1
# define STAIR	(int)2
# define MAIN	(int)3

///Register of characters allows for variable environment
# define ENV_CHARS	(char *)"_0123456789abcdefghijklmnopqrstuvwxyz\
							ABCDEFGHIJKLMNOPQRSTUVWXYZ"

//Typedefs
typedef struct s_redirect	t_redirect;
typedef struct s_cmd		t_cmd;
typedef struct s_kof		t_kof;
typedef struct s_token		t_token;
typedef struct s_block		t_block;
typedef struct s_env		t_env;
typedef struct s_stair		t_stair;
typedef struct s_lstt		t_lstt;
typedef struct s_subarg		t_subarg;
typedef struct s_msh		t_msh;

//Global variable
t_msh						g_msh;

//Structs
struct s_lstt
{
	int			type;
	int			redir_size;
	void		*content;
	t_redirect	*redirect;
	t_lstt		*next;
	t_lstt		*prev;
	int			fd[2];
};

struct s_stair
{
	int		type;
	int		size;
	t_lstt	*node;
	t_stair	*step;
};

struct s_redirect
{
	int		type;
	t_token	*file_tk;
	char	*file;
	int		fd[2];
	int		tmp_fd[2];
};

struct s_cmd
{
	t_token	*args_tk;
	char	*name;
	char	*path;
	char	**args;
};

struct s_token
{
	int			type;
	char		*line;
	int			sub_sh;
	int			sub_shlvl;
	t_subarg	*args;
	t_token		*next;
	t_token		*prev;
};

struct s_subarg
{
	int			type;
	int			quote;
	char		*str;
	int			var_in;
	int			n_wilds;
	t_subarg	*expand;
	t_subarg	*next;
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
	char	*key;
	char	*value;
	t_env	*prev;
	t_env	*next;
};

struct s_msh
{
	t_env	*env;
	t_stair	*stair;
	int		ctrl_c;
	int		err;
};

//Function Declarations
///Debugging Tools
void		print_redirect(t_redirect *redirect, int size);
void		print_cmd(t_cmd *cmd);
void		print_nodes(t_lstt **lst, int depth);
void		print_stairs(t_stair **stair, int depth);
void		print_tokens(t_token **tk);
void		print_matrix(char **matrix);
void		print_subargs(t_subarg **sub, int depth);

///Execution: Main
int			executor(t_stair *st);

///Execution: Utils
int			kill_childs(pid_t *pids, int size);
int			redir_std(int dst[2], const int src[2]);
int			exec_clean(int tmp_fd[2], const int std_fd[2], \
			pid_t *pids, int size);

///Execution: Command
int			expand_args(t_cmd *cmd, t_token **tk);

///Executions: Redirections
int			redirect_node(t_lstt *node);
int			redirect_parser(t_redirect *redir, int size);

///Execution: Expansions
char		*subarg_join(t_subarg **sub);
char		*expand_dollar(t_subarg *expand, int var_in);
int			expand_vars(t_subarg **args);
char		*subarg_expand(t_token *tk);
int			arewildcard(t_subarg **sub);
int			expand_wilds(t_token *tk, t_subarg **args);

///UTILS
char		*ft_strip(char *str);
int			rmqt_size(char *str);
char		*remove_quotes(char *str);

///Parser: Tokens: Synthesize
t_token		*tokenizer(char *str);
t_token		*tk_analyzer(char *str, int *i, int *shlvl, int *limiter);

///Parser: Tokens: Utils
void		*tk_clean(t_token **tk, int mode);
void		tk_addback(t_token **tk, t_token *new);
t_token		*tk_create(char *str, int type, int size, int subsh_lvl);
int			check_tokens(t_token **tk);
int			tk_tkcounter(t_token **tk, int type, int del, int skip_p);
t_token		*tk_copy(t_token *tk);
t_token		*tk_get_in_parenthesis(t_token **tk);
int			tk_isredirection(t_token *tk);
t_token		*tk_dup(t_token **tk);

///Parser: Subargs: Generate
t_subarg	*gen_subargs(char *str, char del);
t_subarg	*extract_subarg(char *str, int *i, char del, int var);

///Parser: Subargs: Utils
t_subarg	*subarg_create(char *str, int size, char quote);
t_subarg	*subarg_var_create(char *str, char del, int *i);
void		*subarg_clean(t_subarg **sub);
void		subarg_addback(t_subarg **args, t_subarg *bottom);
t_subarg	*subarg_dup(t_subarg **sub);
t_subarg	*subarg_copy(t_subarg *sub);

///Parser: Stair: Generate
t_stair		*st_generate(t_token *tk);

///Parser: Stair: Utils
void		st_addfront(t_stair **stair, t_stair *top);
void		*st_clean(t_stair **stair);
t_stair		*st_create(t_lstt *node, int type, int size);

///Parser: Lstt: Utils
void		lstt_addback(t_lstt **list, t_lstt *bottom);
t_redirect	*create_redirect(t_token **tk, int size, int skip_p);
void		*lstt_clean(t_lstt **lst);

///Parser: Cmd: Utils
void		*cmd_clean(t_cmd **cmd);
void		*rd_clean(t_redirect *redirect, int size);
t_token		*cmd_getargs_tk(t_token **tk);

///Parser: Conversor
t_lstt		*tk_to_lstt(t_token **tk);

///Enviroment: Create
t_env		*node_create(char *key, char *value);
void		addfront_env(t_env **msh_env, t_env *tmp);
void		ft_env(char **env);

///Enviroment: Utils
char		**list_to_array(t_env **m_env);
t_env		*env_search(t_env **env, char *key);
char		**sort_env(char **env);
int			print_export(void);
int			clean_env(t_env **list, int ret);
void		env_set_value(t_env **list, char *name, char *value);

///Validate
char		*validate_input(char *input, int *err);
int			start(char *input);

///Validate: Utils
int			check_qp(t_kof *fok, char c);
int			init_kof(t_kof *fok);

///Builtins: Echo
int			exec_echo(char **input);
int			ft_echo_n(char **input);

///Builtins: Pwd
int			exec_pwd(void);

///Builtins: Env
int			print_env(t_env **env);
int			print_one_env(char *input);

///Builtins: Export && Unset
int			export_add(char **input);
int			exec_export(char **nodes);
int			check_export(char *key, char *value);
void		env_unset_node(t_env **env, char *node);
int			exec_unset(t_env **env, char **input);
int			check_unset(char *node);

///Builtins: Exit
int			exec_exit(char **exit);
int			print_exit_error(char *data);

///Builtins: Cd
int			exec_cd(char **input);
int			get_cd_dir(char **input, char **pwd, int *flag);
int			exec_changed(char *pwd, int *flag);
int			env_pwd_change(t_env **env, char *old_pwd, int *flag);
int			exec_builtins(t_cmd *cmd);

///Builtins: Utils
int			validate_args(char **node, int *value);
int			is_valid_num(char *data);
char		*env_node_value(t_env **env, char *key);
int			create_add_node(char *key, char *value);
void		set_null_node(char *key, t_env **env);
int			is_builtin(char *cmd);

///Expand
int			env_var_count(char *str);
int			var_size(char *str);
char		*expand_var(char *str);
char		**fill_env_vars(char *str, int size);
char		*expand_env_var(char *str);
char		*expand_line(char *str);
int			expand(t_token **tk);
int			var_total_size(char *str, char **vars);
char		*var_line(char *str, char **vars, int size);

///Expand: Wildcard
char		*expand_wildcard(char *str);

///Wildcard
char		**get_wildcard(char *directory);
int			ft_count_dir(char *directory);

///Signals
int			init_signals(int mode);
void		norm_handler(int sig, siginfo_t *data, void *non_used_data);
void		ninter_handler(int sig, siginfo_t *data, void *non_used_data);
void		do_sigign(int signum);
void		heredoc_handler(int sig, siginfo_t *data, void *non_used_data);

#endif
