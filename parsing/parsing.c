/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/26 11:42:19 by cgelin           ###   ########.fr       */
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

char	*rmchar_substr(char const *s, unsigned int start, size_t len, char c)
{
	char		*str;
	size_t		i;

	i = 0;
	if (len + start > ft_strlen((char *)s))
		len = ft_strlen((char *)s) - start;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (start >= ft_strlen((char *)s))
		return (str);
	if (str == NULL)
		return (NULL);
	while (i < len && s[i])
	{
		while (s[start + i] == c)
			start++;
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	end_quote(char *line, int i)
{
	if (line[i] == '"' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		return (1);
	return (0);
}

int	strlen_until(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i);
}

char	*rm_quotes(char *line)
{
	char	*res;
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (line[i])
	{	
		start = i;
		while (line[i] && line[i] != '"')
			i++;
		printf("start : %d, i : %d\n", start, i);
		res = ft_substr(line, start, i);
		printf("res1 : %s\n", res);
		if (line[i] && line[i] == '"')
		{
			start = i;
			i++;
			while (line[i] && !end_quote(line, i))
				i++;
			if (i - start)
			{	
				printf("start : %d, i : %d\n", start, i);
				res = rmchar_substr(line, start, i - start, '"');
				printf("res2 : %s\n", res);
			}
		}
		i++;
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
			// msh->cmd[j++].param = ft_split(cmd, ' ');
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
