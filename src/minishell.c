/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:36:26 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/05 14:02:35 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>
#include	<stdlib.h>

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	write (1, "\n", 1);
	return (0);
}
