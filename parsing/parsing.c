/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/27 12:06:55 by colas            ###   ########.fr       */
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
	size_t		i;
	size_t		len;

	i = 0;
	len = end - start;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (str == NULL)
		return (NULL);
	while (i <= len && s[i] && start + i <= end)
	{	
		while (s[start + i] == c)
			start++;
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

int is_last_quote(char *s, int i, int start)
{
	int q_count;

	q_count = 0;
	if (!(s[i + 1] == '"' && (s[i + 2] == ' ' || s[i + 2] == '\0')))
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

	i = 0;
	start = 0;
	res = NULL;
	while (line[i])
	{	
		//place start after first quote
		while (line[start] && (is_white_space(line[start]) || line[start] == '"'))
			start++;
		//place i before quote that comes before space
		i = start;
		while (line[i] && !is_last_quote(line, i, start))
			i++;
		printf("start = %d, i = %d\n", start, i);
		tmp = rmchar_substr(line, start, i, '"');
		printf("tmp : |%s|\n", tmp);
		res = ft_strjoin(res, tmp);
		printf("joined : %s\n", res);
		// go to next word/quote
		start = i+2;
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
			// printf("cmd : %s\n", cmd);
			// msh->cmd[j++].param = ft_split(cmd, '|');
		}
		while (msh->line[i] && !is_delimiter(msh->line, i))
			i++;
	}
	// j = 0;
	// printf("cmd_nbr : %d\n-----\n", msh->cmd_nbr);
	// while (j < msh->cmd_nbr)
	// {
	// 	printf("cmd : %d\n", j);
	// 	printf("param 1: %s\n", msh->cmd[j].param[0]);
	// 	printf("param 2: %s\n", msh->cmd[j++].param[1]);
	// 	printf("---------\n");
	// }
	return (1);
}
