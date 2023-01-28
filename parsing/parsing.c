/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/28 19:18:37 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_cmd_nbr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{	
		if (is_delimiter(str, i))
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
		printf("%lu, %c\n", start + i, str[i]);
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

int	is_end_of_arg(char *s, int i, int start)
{
	int	q_count;

	q_count = 0;
	if (s[i + 1] != ' ')
		return (0);
	while (i >= start)
	{
		if (s[i] == '"')
			q_count++;
		i--;
	}
	if (q_count % 2 == 1)
		return (0);
	return (1);
}

char	*rm_quotes(char *line)
{
	char	*res;
	char	*tmp;
	int		i;
	int		start;
	char	delim;

	start = 0;
	res = NULL;
	i = 0;
	//place start after first quote
	delim = '"';
	while (line[i])
	{	
		while (line[start] && is_white_space(line[start]))
			start++;
		if (line[start] == '\'')
			delim = '\'';
		i = start;
		//place i at end of arg
		while (line[i] && !is_end_of_arg(line, i, start))
			i++;
		printf("start = %d, i = %d\n", start, i);
		tmp = rmchar_substr(line, start, i, delim);
		printf("tmp : |%s|\n", tmp);
		res = ft_strjoin(res, tmp);
		printf("joined : %s\n", res);
		// go to next word/quote
		if (line[i] == delim && line[i + 1] != '\0')
			i++;
		i++;
		start = i;
		printf("start = %d, i = %d\n", start, i);
	}
	return (res);
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
		while (msh->line[i] && (is_delimiter(msh->line, i) \
		|| is_white_space(msh->line[i])))
			i++;
		if (msh->line[i])
		{
			cmd = rm_quotes(ft_substr(msh->line, i, get_size(msh->line, i)));
			printf("cmd : %s\n", cmd);
			msh->cmd[j++].param = ft_split(cmd, '|');
		}
		while (msh->line[i] && !is_delimiter(msh->line, i))
			i++;
	}
	j = 0;
	printf("cmd_nbr : %d\n-----\n", msh->cmd_nbr);
	while (j < msh->cmd_nbr)
	{
		printf("cmd : %d\n", j);
		printf("param 1: %s\n", msh->cmd[j].param[0]);
		printf("param 2: %s\n", msh->cmd[j++].param[1]);
		printf("---------\n");
	}
	return (1);
}
