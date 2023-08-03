/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:05:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 16:43:11 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

void	msh_exit(int status)
{
	ctrl_c(SET);
	rl_clear_history();
	g_msh.err = status;
	st_clean(&g_msh.stair);
	clean_env(&g_msh.env, 0);
	exit(status);
}

static int	print_quote(char *str, int op, int quoted, int last)
{
	char	c;

	c = ':';
	if (last)
		c = '\n';
	if (str && quoted & op)
		return (ft_printf(2, " `%s'%c", str, c));
	if (str)
		return (ft_printf(2, " %s%c", str, c));
	return (0);
}

int	msg_error(char *str, char *added, char *added2, int quoted)
{
	if (ft_printf(2, "Minishell:") == -1)
		return (-1);
	if (print_quote(str, 1, quoted, (!added && !added2)) == -1)
		return (-1);
	if (print_quote(added, 2, quoted, (added2 == NULL)) == -1)
		return (-1);
	if (print_quote(added2, 4, quoted, 1) == -1)
		return (-1);
	return (0);
}
