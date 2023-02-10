/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/10 06:16:01 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_cmd_nbr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_white_space(str[i]))
			count = 1;
		i++;
	}
	i = 0;
	while (str[i])
	{	
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	*getline_rm_quote(char const *s, unsigned int start, size_t end, char c)
{
	char		*str;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * ft_strlen(s));
	if (!str)
		return (NULL);
	while (j < start)
	{
		str[j] = s[j];
		j++;
	}
	i = j;
	while (s[j] && j <= end)
	{
		if (s[j] != c)
			str[i++] = s[j];
		j++;
	}
	while (s[j])
		str[i++] = s[j++];
	str[i] = '\0';
	return (str);
}

int	is_end_of_arg(char *s, int i, int start, int delim)
{
	int	q_count;

	q_count = 0;
	if (!s[i + 1])
		return (1);
	if (s[i + 1] != ' ')
		return (0);
	while (i >= start)
	{
		if (s[i] == delim)
			q_count++;
		i--;
	}
	if (q_count % 2 == 1)
		return (0);
	return (1);
}

int	quote_rm_nbr(char *s, int start, int end, char delim)
{
	int	count;

	count = 0;
	while (start <= end)
	{
		if (s[start] == delim)
			count ++;
		start++;
	}
	return (count);
}

char	*replace_spaces(char *s, int i, char c)
{
	int	j;

	while (s[i] && !is_white_space(s[i]))
	{
		if (s[i] == '\'' || s[i] == '"')
			return (s);
		i++;
	}
	j = i;
	while (s[j] && s[j] != '\'' && s[j] != '"' && is_white_space(s[j]))
		j++;
	while (s[i] && i < j)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

char	*rm_quotes(char *str)
{
	int		i;
	int		j;
	int		start;
	char	quote;
	char	*line;

	i = -1;
	line = str;
	while (line[++i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quote = line[i];
			start = i;
			while (line[i] && !is_end_of_arg(line, i, start, quote))
				i++;
			while (line[i] && line[i] != quote)
				i--;
			j = quote_rm_nbr(line, start, i, quote);
			line = getline_rm_quote(line, start, i, quote);
			i -= j;
			line = replace_spaces(line, i, '|');
		}
	}
	return (line);
}

int	go_after_fd_name(t_msh *msh, int i)
{
	if (msh->line[i] == '>' || msh->line[i] == '<')
	{
		while (msh->line[i] && is_delimiter(msh->line[i]))
			i++;
		while (msh->line[i] && (is_white_space(msh->line[i]) \
		|| is_delimiter(msh->line[i])))
			i++;
		while (msh->line[i] && !is_white_space(msh->line[i]) \
		&& !is_delimiter(msh->line[i]))
			i++;
	}
	return (i);
}

int	parse_line(t_msh *msh)
{
	int		i;
	int		j;
	char	*cmd;
	char	*sub;

	i = 0;
	j = 0;
	msh->cmd_nbr = get_cmd_nbr(msh->line);
	msh->cmd = malloc(sizeof(t_cmd) * msh->cmd_nbr);
	if (!msh->cmd)
		return (0);
	while (msh->line[i])
	{
		while (msh->line[i] && (msh->line[i] == '|' \
		|| is_white_space(msh->line[i])))
			i++;
		i = go_after_fd_name(msh, i);
		if (msh->line[i])
		{
			sub = ft_substr(msh->line, i, get_size(msh->line, i));
			cmd = rm_quotes(sub);
			msh->cmd[j++].param = ft_split(cmd, '|');
		}
		while (msh->line[i] && !is_delimiter(msh->line[i]))
			i++;
	}
	j = 0;
	printf("cmd_nbr : %d\n-----\n", msh->cmd_nbr);
	while (j < msh->cmd_nbr)
	{
		i = 0;
		printf("cmd : %d\n", j);
		while (msh->cmd[j].param[i])
		{
			printf("param [%d]: %s\n", i, msh->cmd[j].param[i]);
			i++;
		}
		j++;
		printf("---------\n");
	}
	return (1);
}
