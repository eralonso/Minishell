/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:04:35 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/05 10:28:17 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int	tk_isredirection(t_token *tk)
{
	if (!tk)
		return (0);
	if (tk->type == RDI || tk->type == RDO || tk->type == RDAP)
		return (1);
	if (tk->type == RDHD)
		return (2);
	return (0);
}
