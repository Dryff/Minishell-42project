/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/19 14:42:15 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*get_dollar(t_msh *msh, t_parse *p)
{
	int	cursor;

	cursor = p->s + 1;
	while (p->line[cursor] && p->line[cursor] != p->q)
	{
		if (p->line[cursor] == '$' && p->q == '"')
			p->line = replace_env_arg(msh, p, cursor);
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

int	is_end_of_arg(t_parse p)
{
	int	q_count;

	q_count = 0;
	if (!p.line[p.i + 1])
		return (1);
	if (p.line[p.i + 1] != ' ')
		return (0);
	while (p.i >= p.s)
	{
		if (p.line[p.i] == p.q)
			q_count++;
		p.i--;
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
