/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:00:02 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/09 14:47:20 by eralonso         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef	struct s_msh
{
	t_env	*env;
	int		err;
}				t_msh;

#endif