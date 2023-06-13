/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subargs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:11:12 by eralonso          #+#    #+#             */
/*   Updated: 2023/06/13 12:29:28 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

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
			subarg_clean(&tmp->expand);
		if (tmp->str)
			free(tmp->str);
		free(tmp);
		tmp = tmp2;
	}
	return (NULL);
}

void	subarg_addback(t_subarg **args, t_subarg *bottom)
{
	t_subarg	*tmp;

	if (!args)
		return ;
	if (!*args)
	{
		*args = bottom;
		return ;
	}
	tmp = *args;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = bottom;
}

t_subarg	*subarg_var_create(char *str, char del, int *i)
{
	t_subarg	*var;

	var = ft_calloc(sizeof(t_subarg), 1);
	if (!var)
		return (NULL);
	var->type = VAR;
	var->quote = del;
	(*i)++;
	var->expand = extract_subarg(str, i, del, 1);
	if (!var->expand)
		return (subarg_clean(&var));
	return (var);
}

t_subarg	*subarg_create(char *str, int size, char quote)
{
	t_subarg	*new;

	new = ft_calloc(sizeof(t_subarg), 1);
	if (!new)
		return (NULL);
	new->quote = quote;
	new->type = TXT;
	if (size)
	{
		new->str = ft_substr(str, 0, size);
		if (!new->str)
			return (subarg_clean(&new));
	}
	return (new);
}

	// printf("suba arg VAR create: str: :%s: && i:%i\n", str, *i);
	// printf("suba arg create: str: :%s: && size:%i\n", str, size);