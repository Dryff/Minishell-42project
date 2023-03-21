/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 02:03:35 by colas             #+#    #+#             */
/*   Updated: 2023/03/21 20:54:02 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*getline_rm_quote(t_msh *msh, t_parse p)
{
	char		*str;
	int			i;
	int			j;

	str = malloc(sizeof(char) * ft_strlen(p.line) + 1);
	if (!str)
		return (error_manager(MALLOC_ERR), NULL);
	i = 0;
	j = -1;
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
	free(p.line);
	return (str[i] = '\0', str);
}

int	is_end_of_arg(int i, char *line, char q, int s)
{
	int q_count;

	q_count = 0;
	if (q)
		if (line[i] != q)
			return (0);
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

char	*replace_spaces_of_expanded(t_parse p, char *line)
{
	int j;

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
