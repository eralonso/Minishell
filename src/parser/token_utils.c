/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:11:52 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/15 13:53:12 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	*tk_clean(t_token **tk, int mode)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!tk || !*tk)
		return (NULL);
	tmp = *tk;
	while (tmp)
	{
		if (mode == NEXT)
			tmp2 = tmp->next;
		else
			tmp2 = tmp->prev;
		if (tmp->line)
			free(tmp->line);
		if (tmp->type == ARG)
			subarg_clean(&tmp->args);
		free(tmp);
		tmp = tmp2;
	}
	*tk = NULL;
	return (NULL);
}

t_token	*tk_copy(t_token *tk)
{
	t_token	*cpy;

	cpy = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!cpy)
		return (NULL);
	cpy->type = tk->type;
	cpy->sub_sh = tk->sub_sh;
	cpy->sub_shlvl = tk->sub_shlvl;
	if (cpy->type != ARG)
	{
		cpy->line = ft_strdup(tk->line);
		if (!cpy->line)
			return (tk_clean(&cpy, NEXT));
	}
	else
	{
		cpy->args = subarg_dup(&tk->args);
		if (!cpy->args)
			return (tk_clean(&cpy, NEXT));
	}
	return (cpy);
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
		((tk_type == OP && (paren++)) || (tk_type == CP && (paren--)));
		paren *= skip_p;
		if ((tk_type == AND || tk_type == OR) && type == LOGIC && !paren)
			count++;
		else if (tk_type == type && !paren)
			count++;
		else if (tk_isredirection(tmp) && type == RD && !paren)
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
	if (type == EOCL)
		return (new);
	new->line = ft_substr(str, 0, size);
	if (!new->line)
		return (tk_clean(&new, NEXT));
	if (type == ARG)
	{
		printf("ARG:\n\n");
		if (!str || !*str)
			new->args = subarg_create("", 1, 0);
		else
			new->args = gen_subargs(new->line, 0);
		ft_free(&new->line, 2);
		if (!new->args)
			return (tk_clean(&new, NEXT));
		print_subargs(&new->args, 0);
	}
	return (new);
}
