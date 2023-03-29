/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils_and_replace_spaces.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 02:03:35 by colas             #+#    #+#             */
/*   Updated: 2023/03/29 10:25:05 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	go_after_pipe(char *line, int i)
{
	while (line[i] && is_white_space(line[i]))
		i++;
	while (line[i] && line[i] == '|')
		i++;
	return (i);
}

int	is_end_of_arg(int i, char *line, char q, int s)
{
	int	q_count;

	q_count = 0;
	if (q)
		if (line[i] != q)
			return (0);
	if (!line[i + 1])
		return (1);
	if (line[i + 1] != ' ' && line[i + 1] != '>' && \
	line[i + 1] != '<' && line[i + 1] != '|')
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

int	go_to_end_quote(int i, char *line, char q, int s)
{
	while (line[i] && !is_end_of_arg(i, line, q, s))
		i++;
	while (i > 0 && line[i] != q)
		i--;
	return (i);
}

char	*replace_spaces_of_expanded(t_parse p, char *line)
{
	printf("%d\n", p.i);
	printf("%s\n", line);
	while (line[p.i])
	{
		if (is_white_space(line[p.i]))
			line[p.i] = 10;
		p.i++;
	}
	return (line);
}

char	*replace_spaces(t_parse p, char *line)
{
	int	j;

	while (line[p.i] && !is_white_space(line[p.i]))
	{
		if (line[p.i] == '\'' || line[p.i] == '"')
			return (line);
		p.i++;
	}
	j = p.i;
	while (line[j] && line[j] != '\'' && line[j] != '"' \
			&& is_white_space(line[j]))
		j++;
	while (line[p.i] && p.i < j)
	{
		line[p.i] = 10;
		p.i++;
	}
	return (line);
}
