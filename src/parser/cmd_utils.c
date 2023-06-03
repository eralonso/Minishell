/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:34:14 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/03 18:00:41 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	*cmd_clean(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return (NULL);
	tmp = *cmd;
	ft_free(&tmp->cmd_n, 2);
	ft_free(&tmp->cmd_path, 2);
	ft_free(tmp->cmd_args, 1);
	free(tmp);
	return (NULL);
}
