/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/10 14:36:37 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>


int check_syntax(char *input, t_kof *fok)
{
    int i;

    i = -1;
    while (input[++i])
    {
        ((input[i] == '\"') && (fok->sq < 0) && (fok->dq *= -1));
        ((input[i] == '\'') && (fok->dq < 0) && (fok->sq *= -1));
        ((input[i] == '(' && (fok->sq < 0 && fok->dq < 0)) && (fok->op++));
        ((input[i] == ')' && (fok->sq < 0 && fok->dq < 0) && \
            fok->op > fok->cp) && (fok->cp++));
        ((ft_strnstr(&input[i], "&&\0") && (fok->sq < 0 && fok->dq < 0) && \
            (fok->cp++)));
    }
    return (0);
}

int validate_input(char *input)
{
    t_kof   fok;
    
    fok.dq = -1;
    fok.sq = -1;
    fok.op = 0;
    fok.cp = 0;
    fok.and = 0;
    fok.or = 0;
    printf("%s\n", input);
    if (check_syntax(input, &fok));
        return (1);
    // if (check_redirect(input));
    //     return (1);
    return (0);
}
