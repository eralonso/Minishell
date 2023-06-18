/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exegg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:35:13 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/18 16:54:37 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	expand_args(t_cmd *cmd, t_token **tk)
{
	t_token	*tmp;
	int		i;

	if (!tk)
		return (1);
	cmd->args = ft_calloc(sizeof(char *),tk_tkcounter(tk, ARG, EOCL, 0) + 1);
	if (!cmd->args)
		return (1);
	tmp = *tk;
	i = 0;
	while (tmp)
	{
		cmd->args[i] = subarg_expand(tmp);
		if (!cmd->args[i])
			return (1);
		i++;
		tmp = tmp->next;
	}
	return (0);
}