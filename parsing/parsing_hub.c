/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/21 14:36:08 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	get_cmd(t_msh *msh, int *i, int j)
{
	char	*cmd;
	char	*sub;
	int		size;

	size = get_cmd_size(msh->line, *i);
	sub = ft_substr(msh->line, *i, size);
	if (!sub)
		return (error_manager(msh, MALLOC_ERR + 1));
	cmd = quotes_dollars_and_redir(msh, sub, j);
	msh->cmd[j].param = ft_split(cmd, 10);
	if (!msh->cmd[j].param)
		return (error_manager(msh, MALLOC_ERR + 2));
	free(cmd);
	*i += size;
}

int	store_cmds_between_pipes(t_msh *msh)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (msh->line[i])
	{
		while (msh->line[i] && is_white_space(msh->line[i]))
			i++;
		if (msh->line[i])
		{
			get_cmd(msh, &i, j);
			j++;
		}
		i = go_after_pipe(msh->line, i);
	}
	return (1);
}

int	check_ascii(t_msh *msh)
{
	int		i;

	i = 0;
	while (msh->line[i])
	{
		if (msh->line[i] < 0 || msh->line[i] > 126)
			return (0);
		i++;
	}
	return (1);
}

int	parse_line(t_msh *msh)
{
	if (!check_ascii(msh))
		return (ctrl_d_exit(msh), 0);
	msh->cmd_nbr = get_cmd_nbr(msh->line);
	if (!msh->cmd_nbr)
		return (0);
	msh->cmd = malloc(sizeof(t_cmd) * msh->cmd_nbr);
	if (!msh->cmd)
		return (error_manager(msh, MALLOC_ERR), 1);
	store_cmds_between_pipes(msh);
	get_and_check_fd(msh);
	return (1);
}
