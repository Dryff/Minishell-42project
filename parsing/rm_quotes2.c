/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 02:03:35 by colas             #+#    #+#             */
/*   Updated: 2023/02/25 21:45:01 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*getline_rm_quote(t_parse p)
{
	char		*str;
	int			i;
	int			j;

	str = malloc(sizeof(char) * ft_strlen(p.line));
	i = 0;
	j = -1;
	if (!str)
		return (NULL);
	while (++j < p.strt)
		str[j] = p.line[j];
	i = j;
	while (p.line[j] && j <= p.i)
	{
		if (p.line[j] != p.q)
			str[i++] = p.line[j];
		j++;
	}
	while (p.line[j])
		str[i++] = p.line[j++];
	return (str[i] = '\0', str);
}

int	is_end_of_arg(int i, char *line, char q, int s)
{
	int	q_count;

	q_count = 0;
	if (!line[i + 1])
		return (1);
	if (line[i + 1] != ' ')
		return (0);
	while (i >= s)
	{
		if (line[i] == q)
			q_count++;
		i--;
	}
	if (q_count % 2 == 1)
		return (0);
	return (1);
}

int	quote_rm_nbr(t_parse p)
{
	int	count;

	count = 0;
	while (p.strt <= p.i)
	{
		if (p.line[p.strt] == p.q)
			count ++;
		p.strt++;
	}
	return (count);
}

char	*replace_spaces(t_parse p)
{
	int	j;

	while (p.line[p.i] && !is_white_space(p.line[p.i]))
	{
		if (p.line[p.i] == '\'' || p.line[p.i] == '"')
			return (p.line);
		p.i++;
	}
	j = p.i;
	while (p.line[j] && p.line[j] != '\'' && p.line[j] != '"' \
			&& is_white_space(p.line[j]))
		j++;
	while (p.line[p.i] && p.i < j)
	{
		p.line[p.i] = '|';
		p.i++;
	}
	return (p.line);
}
