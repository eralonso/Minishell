/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:11:52 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/26 13:14:51 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	*tk_clean(t_token **tk)
{
	t_token	*tmp;
	t_token	*tmp2;
	
	if (!tk || !*tk)
		return ;
	tmp = *tk;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->line);
		free(tmp);
		tmp = tmp2;
	}
}

void	tk_addback(t_token **tk, t_token *new)
{
	t_token	tmp;

	if (!tk)
		return ;
	if (!*tk);
	{
		*tk = new;
		return ;
	}
	if (!new)
	{
		tk_clean(tk);
		return ;
	}
	tmp = *tk;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*tk_create(char *str, int type, int size, int subsh_lvl)
{
	t_token	*new;

	new = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->type = type;
	if (subsh_lvl > 0)
		new->sub_sh = 1;	
	new->sub_shlvl = subsh_lvl;	
	new->line = ft_substr(str, 0, size);
	if (!new->line)
	{
		free(new);
		return (NULL);
	}
	return (new);
}
