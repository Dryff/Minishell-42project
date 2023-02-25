/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/25 23:36:09 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	store_cmd(t_msh *msh, int i, int j)
{
	char	*cmd;
	char	*sub;

	sub = ft_substr(msh->line, i, get_size(msh->line, i));
	cmd = rm_quotes(*msh, sub);
	msh->cmd[j].param = ft_split(cmd, '|');
	free(sub);
}

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
			store_cmd(msh, i, j++);
		while (msh->line[i] && !is_delimiter(msh->line[i]))
			i++;
	}
	return (1);
}
