/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:54:19 by colas             #+#    #+#             */
/*   Updated: 2023/03/03 18:17:31 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

static int	if_no_pipe(char *str, int i)
{
	int count;

	count = 0;
	while (str[i])
	{
		if (!is_white_space(str[i]) && !is_delimiter(str[i]))
			count = 1;
		i++;
	}
	return (count);
}

int	get_cmd_nbr(char *str)
{
	int		count;
	int end_quote;
	int quote;
	int start;
	int i;
	
	i = 0;
	start = 0;
	count = 0;
	count = if_no_pipe(str, i);
	quote = get_quote(str, i);
	end_quote = go_to_end_quote(i, str, quote, i);
	if (count == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quote(str, i, quote, start))
			count++;
		i++;
	}
	return (count);
}