/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:54:19 by colas             #+#    #+#             */
/*   Updated: 2023/04/15 16:05:52 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	is_white_space(char c)
{
	if ((c <= 13 && c >= 9) || c == ' ')
		return (1);
	return (0);
}

int	quote_check(char *str, int i, int *start_quote, int *is_in_quotes)
{
	if (str[i] == '"' || str[i] == '\'')
	{
		if (!*is_in_quotes)
		{
			*is_in_quotes = 1;
			*start_quote = i;
			while (str[i] && (str[i] == '"' || str[i] == '\''))
				i++;
		}
		else if (is_in_quotes)
		{
			if (is_end_quote(str, *start_quote, i))
				*is_in_quotes = 0;
		}
	}
	return (i);
}

int	extension_cmd_nbr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_white_space(str[i]))
			break ;
	return (i);
}

int	get_cmd_nbr(char *str)
{
	int		is_in_quotes;
	int		start_quote;
	int		i;
	int		count;

	count = 1;
	i = extension_cmd_nbr(str);
	if (str[0] == '\0')
		count = 0;
	if (i == (int)ft_strlen(str))
		count = 0;
	i = 0;
	is_in_quotes = 0;
	start_quote = 0;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quotes)
			count++;
		quote_check(str, i, &start_quote, &is_in_quotes);
		i++;
	}
	if (is_in_quotes)
		return (ft_err_printf("msh: Quotes are not closed, close it pls\n"), \
	update_msh_status(1), 0);
	return (count);
}
