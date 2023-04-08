/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:51:10 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/05 14:55:32 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int check_arrow_symbols(t_msh *msh, int i, char c)
{
    int count;

    count = 0;
    while (msh->line[i] == c)
    {
        count++;
        i++;
    }
    while (msh->line[i] && is_white_space(msh->line[i]))
        i++;
    if (count == 3)
        return (printf("msh: syntax error near unexpected token `%c'\n", c), -1);
    else if (count == 4)
        return (printf("msh: syntax error near unexpected token `%c%c'\n", c, c), -1);
    else if (count >= 5)
        return (printf("msh: syntax error near unexpected token `%c%c%c'\n", c, c, c), -1);
    else if (msh->line[i] == '|')
        return (printf("msh: syntax error near unexpected token `|'\n"), -1);
    else if (msh->line[i] == '\0')
        return (printf("msh: syntax error near unexpected token `newline'\n"), -1);
    else if (msh->line[i] == 60 && msh->line[i - 1] == 62)
        return (printf("msh: syntax error near unexpected token `>'\n"), -1);
    else if (msh->line[i] == 62 && msh->line[i - 1] == 60)
        return (printf("msh: syntax error near unexpected token `<'\n"), -1);
    return (i);
}

int check_pipe_symbols(t_msh *msh, int i)
{
    i++;
    while (msh->line[i] && is_white_space(msh->line[i]))
        i++;
    if (msh->line[i] == '\0')
        return (0);
    return(1);
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
        if (!is_in_quotes && (msh->line[i] == '>' || msh->line[i] == '<'))
        {
            i = check_arrow_symbols(msh, i, msh->line[i]);
            if (i == -1)
                return (0);
        }
        if (!is_in_quotes && msh->line[i] == '|')
        {
            if (msh->line[i + 1] == '|')
                 return (printf("msh: syntax error near unexpected token `|'\n"), 0);
            if (!check_pipe_symbols(msh, i))
                return (printf("msh: syntax error near unexpected token `|'\n"), 0);
        }
        quote_check(msh->line, i, &start_quote, &is_in_quotes);
		i++;
	}
    return (1);
}