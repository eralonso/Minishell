/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_stair.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:13:56 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/05 13:37:06 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

static void	print_redirect(t_redirect *redirect, int size)
{
	int		i;

	i = -1;
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

static void	print_cmd(t_cmd *cmd)
{
	int		i;

	i = -1;
	printf("\tCMD: cmd_n: %s ", cmd->cmd_n);
	printf("cmd_args:|");
	while (cmd->cmd_args[++i])
		printf("%s|", cmd->cmd_args[i]);
	printf("\n\n");
}

static void	print_nodes(t_lstt **lst)
{
	t_lstt	*node;
	int		i;

	if (!lst || !*lst)
		return ;
	node = *lst;
	i = 0;
	while (node)
	{
		printf("NODE %i\n", i);
		if (node->redir_size)
			print_redirect(node->redirect, node->redir_size);
		if (node->type == STAIR)
		{
			printf("STAIR: \n");
			print_stair((t_stair **)&node->content);
		}
		else
			print_cmd((t_cmd *)node->content);
		node = node->next;
		i++;
	}
}

void	print_stair(t_stair **stair)
{
	t_stair	*tmp;

	if (!stair || !*stair)
		return ;
	tmp = *stair;
	if (tmp->type != MAIN)
		print_stair(&tmp->step);
	if (tmp->type == MAIN)
		printf("TYPE of STAIR: MAIN\n");
	else if (tmp->type == AND)
		printf("TYPE of STAIR: AND\n");
	else if (tmp->type == OR)
		printf("TYPE of STAIR: OR\n");
	print_nodes(&tmp->node);
}
