/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subargs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:11:12 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/10 13:34:45 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*subarg_clean(t_subarg **sub)
{
	t_subarg	*tmp;
	t_subarg	*tmp2;

	if (!sub || !*sub)
		return (NULL);
	tmp = *sub;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->expand)
			subarg_clean(tmp->expand);
		if (tmp->str)
			free(tmp->str);
		free(tmp);
		tmp = tmp2;
	}
}
