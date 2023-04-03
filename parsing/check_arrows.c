/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:51:10 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/03 13:16:56 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int check_pipes_symbols(t_msh *msh, int i)
{
    int count;

    count = 0;
    if (msh->line[i] == '<')
    {   
        while (msh->line[i] == '<')
        {
            count++;
            i++;
        }
        while (msh->line[i] && is_white_space(msh->line[i]))
            i++;
        if (msh->line[i] == '|')
            return (printf("msh: syntax error near unexpected token `|'\n"), \
            msh_status = 2, 1);
        if (msh->line[i] == '\0')
            return (printf("msh: syntax error near unexpected token `newline'\n"), \
            msh_status = 2, 1);
        exit(1);
    }
    return (i);
}

int check_arrows(t_msh *msh)
{
    int i;
	int	is_in_quotes;
	int	start_quote;

	(void)msh;
    i = 0;
	is_in_quotes = 0;
	start_quote = 0;
	while (msh->line[i])
	{
        if (!is_in_quotes && (msh->line[i] == '>' || msh->line[i] == '<' || msh->line[i] == '|'))
            i = check_pipes_symbols(msh, i);
		quote_check(msh->line, i, &start_quote, &is_in_quotes);
		i++;
	}
    return (0);
}