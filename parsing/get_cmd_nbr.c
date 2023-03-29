/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:54:19 by colas             #+#    #+#             */
/*   Updated: 2023/03/29 10:22:59 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

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

int	get_cmd_nbr(char *str)
{
	int		is_in_quotes;
	int		start_quote;
	int		i;
	int		count;

	count = 1;
	if (str[0] == '\0')
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
	// printf("count = %d\n", count);
	return (count);
}
