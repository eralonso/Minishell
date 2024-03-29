/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:56:51 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 16:43:11 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

static int	check_logo(t_token *tk)
{
	t_token	*prev;
	int		n_type;
	int		p_type;

	if (!tk)
		return (1);
	n_type = tk->next->type;
	prev = tk->prev;
	(prev && (p_type = tk->prev->type));
	return ((n_type == PIPE || n_type == CP || n_type == AND \
			|| n_type == OR || n_type == EOCL) || \
			(prev && (p_type != ARG && p_type != CP)));
}

static int	check_cp(t_token *tk)
{
	t_token	*prev;
	int		n_type;
	int		p_type;

	if (!tk)
		return (1);
	prev = tk->prev;
	n_type = tk->next->type;
	(prev && (p_type = tk->prev->type));
	return ((n_type == ARG || n_type == OP) || \
			(prev && (p_type != ARG && p_type != CP)));
}

static int	check_op(t_token *tk)
{
	t_token	*prev;
	int		n_type;
	int		p_type;

	if (!tk)
		return (1);
	prev = tk->prev;
	n_type = tk->next->type;
	(prev && (p_type = tk->prev->type));
	return ((n_type == PIPE || n_type == CP || n_type == AND \
			|| n_type == OR || n_type == EOCL) || \
			(prev && (p_type != PIPE && p_type != OP \
			&& p_type != AND && p_type != OR)));
}

static int	check_pipe(t_token *tk)
{
	t_token	*prev;
	int		n_type;
	int		p_type;

	if (!tk)
		return (1);
	prev = tk->prev;
	n_type = tk->next->type;
	(prev && (p_type = tk->prev->type));
	return ((n_type == PIPE || n_type == CP || n_type == AND \
			|| n_type == OR || n_type == EOCL) || \
			(!prev || (p_type != ARG && p_type != LIMITER && p_type != CP)));
}

int	check_tokens(t_token **tk)
{
	t_token	*tmp;
	int		err;

	(1 && (tmp = *tk) && (err = 0));
	while (tmp && tmp->type != EOCL && err == 0)
	{
		(tmp->type == ARG && (tmp->next->type == OP \
			|| (tmp->prev && tmp->prev->type == CP)) && (err = ARG));
		(tmp->type == PIPE && check_pipe(tmp) && (err = PIPE));
		(tmp->type == OP && check_op(tmp) && (err = OP));
		(tmp->type == CP && check_cp(tmp) && (err = CP));
		((tmp->type == AND || tmp->type == OR) && check_logo(tmp) \
			&& (err = tmp->type));
		((tmp->type == RDI || tmp->type == RDO || tmp->type == RDAP) \
		&& tmp->next->type != ARG && (err = tmp->type));
		(tmp->type == RDHD && tmp->next->type != LIMITER && (err = RDHD));
		tmp = tmp->next;
	}
	return (msg_syntax_error(err, err));
}
