/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_stair.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:13:56 by eralonso          #+#    #+#             */
/*   Updated: 2023/08/03 12:11:31 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

void	print_redirect(t_redirect *redirect, int size)
{
	int		i;

	i = -1;
	if (!redirect)
		return ;
	printf("Redirections:\n\t");
	while (++i < size)
	{
		printf("type:");
		if (redirect[i].type == RDI)
			printf("Input: ");
		else if (redirect[i].type == RDO)
			printf("Output: ");
		else if (redirect[i].type == RDAP)
			printf("Append: ");
		else if (redirect[i].type == RDHD)
			printf("Here Doc: ");
		printf(" file/limiter:%s:\n\t", redirect[i].file);
	}
	printf("\n");
}

void	print_cmd(t_cmd *cmd)
{
	int		i;

	i = -1;
	if (!cmd)
		return ;
	printf("\tCMD: ");
	if (cmd->args)
	{
		printf("args:|");
		while (cmd->args[++i])
			printf("%s|", cmd->args[i]);
	}
	printf("\n\n");
}

void	print_nodes(t_lstt **lst, int depth)
{
	t_lstt	*node;
	int		i;

	if (!lst || !*lst)
		return ;
	node = *lst;
	i = 0;
	while (node)
	{
		printf("DEPTH: %i | NODE: %i\n", depth, i);
		if (node->redir_size)
			print_redirect(node->redirect, node->redir_size);
		if (node->type == STAIR)
		{
			printf("STAIR: \n");
			print_stairs((t_stair **)&node->content, depth + 1);
		}
		else
			print_cmd((t_cmd *)node->content);
		node = node->next;
		i++;
	}
}

void	print_stairs(t_stair **stair, int depth)
{
	t_stair	*tmp;

	if (!stair || !*stair)
		return ;
	tmp = *stair;
	if (tmp->type != MAIN)
		print_stairs(&tmp->step, depth);
	if (tmp->type == MAIN)
		printf("TYPE of STAIR: MAIN\n");
	else if (tmp->type == AND)
		printf("TYPE of STAIR: AND\n");
	else if (tmp->type == OR)
		printf("TYPE of STAIR: OR\n");
	printf("SIZE: %i\n", tmp->size);
	print_nodes(&tmp->node, depth);
}
