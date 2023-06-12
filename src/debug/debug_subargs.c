/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_subargs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:32:46 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/12 18:35:20 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

void	print_subargs(t_subarg **sub, int depth)
{
	t_subarg	*tmp;
	t_subarg	*tmp2;

	if (!sub || !*sub)
		return ;
	tmp = *sub;
	while (tmp)
	{
		printf("%*c%i SubArg:\n", depth * 3, '\0', depth);
		tmp2 = tmp->next;
		printf("\tType:%5c", ' ');
		if (tmp->type == WILD)
			printf("WILD\n");
		if (tmp->type == TXT)
			printf("TXT\n");
		if (tmp->type == VAR)
			printf("VAR\n");
		printf("\tQuote:%5c", ' ');
		if (!tmp->quote)
			printf(" \\0\n");
		else
			printf(" %c\n", tmp->quote);
		printf("\tStr:%5c:%s:\n", ' ', tmp->str);
		if (tmp->expand)
		{
			printf("%*c%i   EXPAND:\n", depth * 3, '\0', depth);
			print_subargs(&tmp->expand, depth + 1);
		}
		tmp = tmp2;
	}
}