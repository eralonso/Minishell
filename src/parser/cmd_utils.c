/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:34:14 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/05 12:29:32 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

static int	cmd_countargs(t_token **tk)
{
	t_token	*tmp;
	int		count;

	if (!tk || !*tk || (*tk)->type == EOCL)
		return (0);
	tmp = *tk;
	count = 0;
	while (tmp && tmp->type != EOCL)
	{
		if (tk_isredirection(tmp))
			tmp = tmp->next;
		else if (tmp->type == ARG)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**cmd_getargs(t_token **tk)
{
	char	**args;
	int		i;
	t_token	*tmp;

	if (!tk || !*tk)
		return (NULL);
	tmp = *tk;
	i = 0;
	args = (char **)ft_calloc(sizeof(char *), cmd_countargs(tk) + 1);
	if (!args)
		return (NULL);
	while (tmp && tmp->type != EOCL)
	{
		if (tk_isredirection(tmp))
			tmp = tmp->next;
		else if (tmp->type == ARG)
		{
			args[i] = ft_strdup(tmp->line);
			if (!args[i++])
				return (ft_free(args, 1));
		}
		tmp = tmp->next;
	}
	return (args);
}

char	*cmd_getcommand(t_token **tk)
{
	t_token	*tmp;

	if (!tk || !*tk)
		return (NULL);
	tmp = *tk;
	while (tmp && tmp->type != EOCL)
	{
		if (tmp->type == ARG && !tk_isredirection(tmp->prev))
			return (ft_strdup(tmp->line));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
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
	free(tmp);
	return (NULL);
}
