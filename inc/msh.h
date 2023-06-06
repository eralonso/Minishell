/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:00:02 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/06 17:52:32 by eralonso         ###   ########.fr       */
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

//Defines
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

///
# define NEXT	(int)0
# define PREV	(int)1

///Types of tokens: 
////EOCL == End Of Command Line, RDHD == ReDirection Here Doc '<<',
////PIPE == Pipe '|', RDAP == ReDirection APpend '>>',
////RDI == ReDirection Input '<', AND == And '&&', 
////RDO == ReDirection Output '>', OR == Or '||', 
////OP == Open Parenthesis '(', ARG == Argument == 
////Text {[A ... Z], [a ... z], [0 ... 9]}, CP == Close Parenthesis ')',
////LOGIC == LOGIC operator {&&, ||}, RD == ReDirections == {<, >, <<, >>}
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
# define LOGIC	(int)11
# define RD		(int)12

///Type of node: MAIN == First Step, CMD == CoMmanD, STAIR == subshell/stair
# define CMD	(int)1
# define STAIR	(int)2
# define MAIN	(int)3

//Typedefs
typedef struct s_redirect	t_redirect;
typedef struct s_cmd		t_cmd;
typedef struct s_kof		t_kof;
typedef struct s_token		t_token;
typedef struct s_block		t_block;
typedef struct s_env		t_env;
typedef struct s_stair		t_stair;
typedef struct s_lstt		t_lstt;
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
};

struct s_stair
{
	int		type;
	int		size;
	int		final_idx;
	t_lstt	*node;
	t_stair	*step;
};

struct s_redirect
{
	int		type;
	char	*file;
	int		fd[2];
	int		tmp_fd[2];
};

struct s_cmd
{
	char	*cmd_n;
	char	*cmd_path;
	char	**cmd_args;
};

struct s_token
{
	int		type;
	char	*line;
	int		sub_sh;
	int		sub_shlvl;
	int		idx;
	t_token	*next;
	t_token	*prev;
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
	t_stair	*stair;
	int		err;
};

//Function Declarations
///Debugging Tools
void		print_stair(t_stair **stair, int depth);
void		print_tokens(t_token **tk);

///Parser: Tokens: Synthesize
t_token		*tokenizer(char *str);
t_token		*tk_analyzer(char *str, int *i, int *shlvl, int idx);

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
char		*cmd_getcommand(t_token **tk);
char		**cmd_getargs(t_token **tk);

///Parser: Conversor
t_lstt		*tk_to_lstt(t_token **tk);

///Enviroment: Create
t_env		*node_create(char *key, char *value);
void		addfront_env(t_env **msh_env, t_env *tmp);
void		ft_env(char **env);

///Enviroment: Utils
char		**list_to_array(t_env **m_env);
t_env		*env_search(t_env *list, char *key);
void		env_unset_node(t_env *env, char	*node);
int			exec_unset(t_env **env, char *node);
char		**sort_env(char **env);
void		print_export(void);

///Validate
int			validate_input(char *input);

///Validate: Utils
int			check_qp(t_kof *fok, char c);
int			init_kof(t_kof *fok);
char		*ft_strip(char *str);

///Builtins
int			ft_echo(char **input);
int			ft_echo_n(char **input);
int			ft_pwd(char *input);
void		print_env(t_env *env);
int			print_one_env(char *input);

#endif