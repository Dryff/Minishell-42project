/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:51:10 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/13 22:20:40 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	check_arrow_after_arrow(t_msh *msh, int i)
{
	while (msh->line[i] && is_white_space(msh->line[i]))
		i++;
	if (msh->line[i] == '>' && msh->line[i + 1] == '>')
		return (printf("%s `>>'\n", ERR_MESS), -1);
	else if (msh->line[i] == '>')
		return (printf("%s `>'\n", ERR_MESS), -1);
	else if (msh->line[i] == '<' && msh->line[i + 1] == '<')
		return (printf("%s `<<'\n", ERR_MESS), -1);
	else if (msh->line[i] == '<')
		return (printf("%s `<'\n", ERR_MESS), -1);
	return (0);
}

int	check_arrow_symbols(t_msh *msh, int i, char c)
{
	int	count;

	count = 0;
	while (msh->line[i] == c)
	{
		count++;
		i++;
	}
	while (msh->line[i] && is_white_space(msh->line[i]))
		i++;
	if (count == 3)
		return (printf("%s `%c'\n", ERR_MESS, c), -1);
	else if (count == 4)
		return (printf("%s `%c%c'\n", ERR_MESS, c, c), -1);
	else if (count >= 5)
		return (printf("%s `%c%c%c'\n", ERR_MESS, c, c, c), -1);
	else if (msh->line[i] == '|')
		return (printf("%s `|'\n", ERR_MESS), -1);
	else if (msh->line[i] == '\0')
		return (printf("%s `newline'\n", ERR_MESS), -1);
	if (check_arrow_after_arrow(msh, i) == -1)
		return (-1);
	return (i);
}

int	check_pipe_symbols(t_msh *msh, int i)
{
	i++;
	while (msh->line[i] && is_white_space(msh->line[i]))
		i++;
	if (msh->line[i] == '\0')
		return (0);
	return (1);
}

int	check_pipe(t_msh *msh, int i)
{
	if (msh->line[i + 1] == '|')
		return (printf("%s `|'\n", ERR_MESS), 0);
	if (!check_pipe_symbols(msh, i))
		return (printf("%s `|'\n", ERR_MESS), 0);
	return (1);
}

int	check_arrows(t_msh *msh)
{
	int	i;
	int	is_in_quotes;
	int	start_quote;

	i = 0;
	is_in_quotes = 0;
	start_quote = 0;
	while (msh->line[i])
	{
		if (!is_in_quotes && (msh->line[i] == '>' || msh->line[i] == '<'))
		{
			i = check_arrow_symbols(msh, i, msh->line[i]);
			if (i == -1)
				return (update_msh_status(2), 0);
		}
		if (!is_in_quotes && msh->line[i] == '|')
			if (!check_pipe(msh, i))
				return (0);
		quote_check(msh->line, i, &start_quote, &is_in_quotes);
		i++;
	}
	return (1);
}
