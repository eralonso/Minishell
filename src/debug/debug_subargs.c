/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_subargs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:32:46 by eralonso          #+#    #+#             */
/*   Updated: 2023/07/13 16:43:11 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

static void	print_expand(t_subarg *tmp, int depth)
{
	if (tmp->expand)
	{
		printf("%*c%i   EXPAND:\n", depth * 3, '\0', depth);
		print_subargs(&tmp->expand, depth + 1);
	}
}

static void	print_quote(t_subarg *tmp)
{
	printf("\tQuote:%5c", ' ');
	if (!tmp->quote)
		printf(" \\0\n");
	else
		printf(" %c\n", tmp->quote);
}

static void	print_type(t_subarg *tmp)
{
	printf("\tType:%5c", ' ');
	if (tmp->type == WILD)
		printf("WILD\n");
	if (tmp->type == TXT)
		printf("TXT\n");
	if (tmp->type == VAR)
		printf("VAR\n");
}

void	print_subargs(t_subarg **sub, int depth)
{
	t_subarg	*tmp;
	t_subarg	*tmp2;

	if (!sub || !*sub)
		return ;
	tmp = *sub;
	while (tmp)
	{
		tmp2 = tmp->next;
		printf("%*c%i SubArg:\n", depth * 3, '\0', depth);
		print_type(tmp);
		print_quote(tmp);
		printf("\tIn:%5c %i\n", ' ', tmp->var_in);
		printf("\tStr:%5c:%s:\n", ' ', tmp->str);
		print_expand(tmp, depth);
		tmp = tmp2;
	}
}
