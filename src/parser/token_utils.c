/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:11:52 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/03 13:42:28 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	*tk_clean(t_token **tk)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!tk || !*tk)
		return (NULL);
	tmp = *tk;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->line);
		free(tmp);
		tmp = tmp2;
	}
	return (NULL);
}

void	tk_cut(t_token **tk)
{
	if (!tk || !*tk || (*tk)->type == EOCL)
		return ;
	(*tk)->prev->next = NULL;
	*tk = (*tk)->next;
}

int	tk_tkcounter(t_token **tk, int type, int del, int skip_p)
{
	int		count;
	int		tk_type;
	int		paren;
	t_token	*tmp;

	if (!tk || !*tk)
		return (0);
	(0 || ((tmp = *tk) && 0) || (count = 0) || (paren = 0));
	while (tmp && (tmp->type != del || paren))
	{
		tk_type = tmp->type;
		(tk_type == OP && (paren++));
		(tk_type == CP && (paren--));
		paren *= skip_p;
		if ((tk_type == AND || tk_type == OR) && type == LOGIC && !paren)
			count++;
		else if (tk_type == type)
			count++;
		else if ((tk_type == RDI || tk_type == RDO || tk_type == RDAP \
		|| tk_type == RDHD) && type == RD && !paren)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	tk_addback(t_token **tk, t_token *new)
{
	t_token	*tk_tmp;

	if (!tk)
		return ;
	if (!*tk)
	{
		*tk = new;
		return ;
	}
	tk_tmp = *tk;
	while (tk_tmp->next)
		tk_tmp = tk_tmp->next;
	tk_tmp->next = new;
	tk_tmp->next->prev = tk_tmp;
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
	if (type != EOCL)
	{
		new->line = ft_substr(str, 0, size);
		if (!new->line)
		{
			free(new);
			return (NULL);
		}
	}
	return (new);
}
