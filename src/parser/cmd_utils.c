/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:34:14 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/03 13:37:32 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	*rd_clean(t_redirect *redirect, int size)
{
	int	i;

	if (!redirect)
		return (NULL);
	i = -1;
	while (++i < size)
		free(redirect[i].file);
	free(redirect);
	return (NULL);
}

void	*cmd_clean(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return (NULL);
	tmp = *cmd;
	ft_free(&tmp->cmd_n, 2);
	ft_free(&tmp->cmd_path, 2);
	ft_free(tmp->cmd_args, 1);
	rd_clean(tmp->redirect, tmp->rd_num);
	free(tmp);
	return (NULL);
}
