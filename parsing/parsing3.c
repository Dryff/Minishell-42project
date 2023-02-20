/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/20 02:14:04 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*get_dollar(t_msh *msh, t_parse *p)
{
	int	cursor;
	int	end_quote_pos;

	cursor = p->s + 1;
	end_quote_pos = go_to_end_quote(cursor, p->line, p->q, p->s);
	printf("end_quote pos : %d\n", end_quote_pos);
	while (p->line[cursor] && cursor != end_quote_pos)
	{
		if (p->line[cursor] == '$' && p->q == '"')
		{
			printf("avant : %s\n", &p->line[cursor]);
			p->line = replace_env_arg(msh, p, cursor);
		}
		cursor++;
	}
	return (p->line);
}

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
	while (++j < p.s)
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
	while (p.s <= p.i)
	{
		if (p.line[p.s] == p.q)
			count ++;
		p.s++;
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
		p.line[p.i] = 10;
		p.i++;
	}
	return (p.line);
}
