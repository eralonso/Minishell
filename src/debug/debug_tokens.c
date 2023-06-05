/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:55:19 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/05 19:03:10 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	print_tokens(t_token **tk)
{
	t_token	*tmp;

	if (!tk || !*tk)
		return ;
	tmp = *tk;
	while (tmp && tmp->type != EOCL)
	{
		printf("type:");
		((tmp->type == ARG) && printf(" ARG "));
		((tmp->type == OP) && printf(" OP "));
		((tmp->type == CP) && printf(" CP "));
		((tmp->type == RDI) && printf(" RDI "));
		((tmp->type == RDO) && printf(" RDO "));
		((tmp->type == RDAP) && printf(" RDAP "));
		((tmp->type == RDHD) && printf(" RDHD "));
		((tmp->type == PIPE) && printf(" PIPE "));
		((tmp->type == AND) && printf(" AND "));
		((tmp->type == OR) && printf(" OR "));
		printf("line :%s: subsh_lvl == %i\n", tmp->line, tmp->sub_shlvl);
	}
}
