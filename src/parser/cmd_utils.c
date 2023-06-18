/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:34:14 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/18 16:41:08 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

t_token	*cmd_getargs_tk(t_token **tk)
{
	t_token	*args;
	t_token	*tmp;
	t_token	*node;
	int		i;

	if (!tk || !*tk)
		return (NULL);
	tmp = *tk;
	(0 || (i = 0) || (args = NULL));
	while (tmp && tmp->type != EOCL)
	{
		if (tk_isredirection(tmp))
			tmp = tmp->next;
		else if (tmp->type == ARG)
		{
			node = tk_copy(tmp);
			if (!node)
				return (tk_clean(&args, NEXT));
			tk_addback(&args, node);
		}
		tmp = tmp->next;
	}
	if (!args)
		args = tk_create(NULL, ARG, 1, (*tk)->sub_shlvl);
	return (args);
}

void	*cmd_clean(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return (NULL);
	tmp = *cmd;
	tk_clean(&tmp->args_tk, NEXT);
	ft_free(&tmp->name, 2);
	ft_free(&tmp->path, 2);
	ft_free(tmp->args, 1);
	free(tmp);
	return (NULL);
}
