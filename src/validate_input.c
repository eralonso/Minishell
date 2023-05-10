/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos-m <pramos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:49 by pramos-m          #+#    #+#             */
/*   Updated: 2023/05/10 12:58:57 by pramos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<msh.h>

int check_syntax(char *input)
{
    if (ft_strchr(input, "'") || ft_strchr(input, '"'))
    {
        
    }
    if (ft_strchr(input, "(") || ft_strchr(input, ")"))
    {
        
    }
    return (0);
}

int validate_input(char *input)
{
    printf("%s\n", input);
    if (check_syntax(input));
        return (1);
    // if (check_redirect(input));
    //     return (1);
    return (0);
}
