/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:07:58 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/25 18:06:39 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	is_white_space(char c)
{
	if ((c <= 13 && c >= 9) || c == ' ')
		return (1);
	return (0);
}

int	is_delimiter(char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<' \
	|| (str[i] == '>' && str[i + 1] == '>') \
	|| (str[i] == '<' && str[i + 1] == '<'))
		return (1);
	return (0);
}

int	get_size(char *s, int i)
{
	int size;

	size = 0;
	while (s[i] && !is_delimiter(s, i++))
		size++;
	return (size);
}
