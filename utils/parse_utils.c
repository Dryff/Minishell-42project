/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:07:58 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/22 17:00:31 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	is_white_space(char c)
{
	if ((c <= 13 && c >= 9) || c == ' ')
		return (1);
	return (0);
}

int	is_delimiter(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	get_quote(char *s, int i)
{
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (s[i]);
		i++;
	}
	return (0);
}

int	is_end_quote(char *str, int start_quote, int i)
{
	int count;
	
	count = 0;
	while (i >= start_quote)
	{
		// dprintf(2, "in end_quote : i = %d, start_quote = %d\n", i, start_quote);
		if (str[i] == str[start_quote])
			count++;
		i--;
	}
	if (count % 2 == 1)
		return (0);
	return (1);
}

int	get_cmd_size(char *str, int start)
{
	int		is_in_quotes;
	int		start_quote;
	int		i;
	
	i = start;
	is_in_quotes = 0;
	start_quote = 0;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quotes)
			break;
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!is_in_quotes)
			{
				is_in_quotes = 1;
				start_quote = i;
				while (str[i] && str[i] == '"' || str[i] == '\'')
					i++;
			}
			else if (is_in_quotes)
				if (is_end_quote(str, start_quote, i))
					is_in_quotes = 0;
		}
		i++;
	}
	return (i - start);
}

