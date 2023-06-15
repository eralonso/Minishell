/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:34:14 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/15 13:45:34 by eralonso         ###   ########.fr       */
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
	i = 0;
	args = NULL;
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
	return (args);
}

t_token	*cmd_getname_tk(t_token **tk)
{
	t_token	*tmp;

	if (!tk || !*tk)
		return (NULL);
	tmp = *tk;
	while (tmp && tmp->type != EOCL)
	{
		if (tmp->type == ARG && !tk_isredirection(tmp->prev))
			return (tk_copy(tmp));
		tmp = tmp->next;
	}
	return (tk_create("", ARG, 1, (*tk)->sub_shlvl));
}

void	*cmd_clean(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return (NULL);
	tmp = *cmd;
	tk_clean(&tmp->cmd_n_tk, NEXT);
	tk_clean(&tmp->cmd_args_tk, NEXT);
	ft_free(&tmp->cmd_n, 2);
	ft_free(&tmp->cmd_path, 2);
	ft_free(tmp->cmd_args, 1);
	free(tmp);
	return (NULL);
}
