/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_to_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:19:54 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/02 10:54:23 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>



// t_token	*tk_ncpy(t_token *start, t_token *end)
// {
// 	return ();
// }

// t_block	*tk_to_block(t_token **tk)
// {
// 	t_block	*bk;
// 	t_block	*node;
// 	t_token	*tk_iter;
// 	t_token	*tmp;

// 	if (!tk)
// 		return (NULL);
// 	(0 || (bk = NULL) || (tk_iter = *tk));
// 	while (tk_iter)
// 	{
// 		tmp = tk_iter;
// 		while (tk_iter->type != EOCL && tk_iter->type != AND \
// 		&& tk_iter->type != OR && tk_iter->type != OP && tk_iter->type != CP)
// 			tk_iter = tk_iter->next;
// 		node = tk_ncpy(tmp, tk_iter);
// 		if (tk_iter->type == CP)
// 			return (node);
// 		if (tk_iter->type == OP)
// 			node = tk_to_block();
// 		tk_bk_addback(&bk, node, BK);
// 	}
// 	return (bk);
// }
