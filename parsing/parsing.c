/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/09 16:31:39 by colas            ###   ########.fr       */
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

char	*rmchar_substr(char const *s, unsigned int start, size_t end, char c)
{
	char		*str;
	char		delim;
	size_t		i;
	size_t		len;

	i = 0;
	len = end - start;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	delim = '\'';
	if (c == '\'')
		delim = '"';
	while (i <= len && s[i] && start + i <= end)
	{	
		while (s[start + i] == c)
			start++;
		while (s[start + i] == delim && s[start + i + 1] == delim)
			start += 2;
		if (start + i <= end)
			str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	strlen_until(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i);
}

int	is_end_of_arg(char *s, int i, int start, int delim)
{
	int	q_count;

	q_count = 0;
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

char	*rm_quotes(char *line)
{
	char	*tmp[3];
	int		i;
	int		start;
	char	delim;

	start = 0;
	tmp[2] = NULL;
	tmp[1] = NULL;
	i = 0;
	// place start after first quote
	delim = 10;
	while (line[i])
	{	
		while (line[start] && is_white_space(line[start]))
				start++;
		i = start;
		while (line[i] && !is_end_of_arg(line, i, start, delim))
		{
			// place i at end of arg
			start = i;
			while (line[i] && !is_end_of_arg(line, i, start, delim))
			{
				if (line[i] == '\'' && delim != '"')
					delim = '\'';
				else if (line[i] == '"' && delim != '\'')
					delim = '"';
				i++;
			}
			//go to last quote
			// printf("1i = %d, delim = %c\n", i, delim);
			while (line[i] && line[i] > 0 && line[i] != delim)
				i--;
			// printf("2start = %d, i = %d, delim = %c\n", start, i, delim);
			tmp[0] = rmchar_substr(line, start, i, delim);
			// printf("tmp[0] = %s\n", tmp[0]);
			tmp[1] = ft_strjoin(tmp[1], tmp[0]);
			// printf("tmp[1] = %s\n", tmp[1]);
			delim = 10;
			if (!is_end_of_arg(line, i, start, delim))
				i++;
		}
		// printf("tmp[2] : |%s|\n", tmp[1]);
		tmp[2] = ft_strjoin_by_sep(tmp[2], tmp[1]);
		// printf("joined : %s\n", tmp[1]);
		// go to next word/quote
		if (line[i] && line[i] == delim && line[i + 1] != '\0')
			i++;
		if (line[i])
			i++;
		start = i;
		// printf("start = %d, i = %d\n", start, i);
	}
	return (tmp[2]);
}

int go_after_fd(t_msh *msh, int i)
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

	i = 0;
	j = 0;
	msh->cmd_nbr = get_cmd_nbr(msh->line);
	msh->cmd = malloc(sizeof(t_cmd) * msh->cmd_nbr);
	while (msh->line[i])
	{
		while (msh->line[i] && (msh->line[i] == '|' \
		|| is_white_space(msh->line[i])))
			i++;
		i = go_after_fd(msh, i);
		if (msh->line[i])
		{
			cmd = rm_quotes(ft_substr(msh->line, i, get_size(msh->line, i)));
			// printf("cmd : %s\n", cmd);
			msh->cmd[j++].param = ft_split(cmd, '|');
		}
		while (msh->line[i] && !is_delimiter(msh->line[i]))
			i++;
	}
	// j = 0;
	// printf("cmd_nbr : %d\n-----\n", msh->cmd_nbr);
	// while (j < msh->cmd_nbr)
	// {
	// 	i = 0;
	// 		printf("cmd : %d\n", j);
	// 	while (msh->cmd[j].param[i])
	// 	{
	// 		printf("param [%d]: %s\n", i, msh->cmd[j].param[i]);
	// 		i++;
	// 	}
	// 	j++;
	// 	printf("---------\n");
	// }
	return (1);
}
