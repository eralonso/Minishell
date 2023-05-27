/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:11:52 by eralonso          #+#    #+#             */
/*   Updated: 2023/05/27 18:38:47 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	*bk_clean(t_block **bk)
{
	t_block	*bk_tmp;
	t_block	*bk_tmp2;

	if (!bk || !*bk)
		return (NULL);
	bk_tmp = *bk;
	while (bk_tmp)
	{
		bk_tmp2 = bk_tmp;
		tk_clean(&bk_tmp->tk);
		free(bk_tmp);
		bk_tmp = bk_tmp2;
	}	
	return (NULL);
}

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

void	tk_bk_addback(void **tk, void *new, int type)
{
	t_token	*tk_tmp;
	t_block	*bk_tmp;

	if (!tk)
		return ;
	if (!*tk)
	{
		*tk = new;
		return ;
	}
	((type == TK && (tk_tmp = (t_token *)*tk)) || (bk_tmp = (t_block *)*tk));
	if (type == TK)
	{
		while (tk_tmp->next)
			tk_tmp = tk_tmp->next;
		tk_tmp->next = (t_token *)new;
	}
	else
	{
		while (bk_tmp->next)
			bk_tmp = bk_tmp->next;
		bk_tmp->next = (t_block *)new;
	}
}

t_block	*bk_create(t_token *tk, int sep)
{
	t_block	*new;

	new = ft_calloc(sizeof(t_block), 1);
	if (!new)
		return (NULL);
	new->tk = tk;
	new->sep = sep;
	return (new);
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
