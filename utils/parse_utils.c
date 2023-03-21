/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:07:58 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/21 18:54:01 by cgelin           ###   ########.fr       */
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

// int	is_in_quote(char *s, int i, char quote, int start)
// {
// 	int q_count;

// 	q_count = 0;
// 	while (i >= start)
// 	{
// 		if (s[i] == quote)
// 			q_count++;
// 		i--;
// 	}
// 	if (q_count % 2 == 0)
// 		return (0);
// 	return (1);
// }

// int	get_size(char *s, int i)
// {
// 	int	size;
// 	int end_quote;
// 	int quote;
// 	int start;

// 	size = 0;
// 	quote = get_quote(s, i);
// 	end_quote = go_to_end_quote(i, s, quote, i);
// 	printf("end_quote : %d\n", end_quote);
// 	start = i;
// 	while (s[i])
// 	{
// 		if (s[i] == '|' && !is_in_quote(s, i, quote, start))
// 			break ;
// 		i++;
// 		size++;
// 	}
// 	return (size);
// }

int	is_end_quote(char *str, int start_quote, int i)
{
	int count;
	
	count = 0;
	while (i >= start_quote)
	{
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

