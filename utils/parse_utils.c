/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:07:58 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/03 15:01:51 by colas            ###   ########.fr       */
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

int	is_in_quote(char *s, int i, char quote, int start)
{
	int q_count;

	q_count = 0;
	while (i >= start)
	{
		if (s[i] == quote)
			q_count++;
		i--;
	}
	if (q_count % 2 == 0)
		return (0);
	return (1);
}

int	get_size(char *s, int i)
{
	int	size;
	int end_quote;
	int quote;
	int start;

	size = 0;
	quote = get_quote(s, i);
	end_quote = go_to_end_quote(i, s, quote, i);
	start = i;
	while (s[i])
	{
		if (s[i] == '|' && !is_in_quote(s, i, quote, start))
			break ;
		i++;
		size++;
	}
	return (size);
}
