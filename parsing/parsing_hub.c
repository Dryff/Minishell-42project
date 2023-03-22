/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/22 20:57:50 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	get_cmd(t_msh *msh, int *i, int j)
{
	char	*cmd;
	char	*sub;
	int		size;
	
	size = get_cmd_size(msh->line, *i);
	printf("size = %d\n", size);
	sub = ft_substr(msh->line, *i, size);
	if (!sub)
		return (error_manager(msh, MALLOC_ERR + 1));
	printf("sub = %s\n", sub);
	cmd = quotes_dollars_and_redir(msh, sub, j, *i);
	printf("cmd = %s\n", cmd);
	msh->cmd[j].param = ft_split(cmd, 10);
	if (!msh->cmd[j].param)
		return (error_manager(msh, MALLOC_ERR + 2));
	free(cmd);
	*i += size;
}

int	go_to_arg_start(char *line, int i)
{
	while (line[i] && is_white_space(line[i]))
		i++;
	return (i);
}

int	go_after_pipe(char *line, int i)
{
	while (line[i] && is_white_space(line[i]))
		i++;
	while (line[i] && line[i] == '|')
		i++;
	return (i);
}

int	store_cmds_between_pipes(t_msh *msh)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (msh->line[i])
	{
		i = go_to_arg_start(msh->line, i);
		if (msh->line[i])
		{
			get_cmd(msh, &i, j);
			j++;
		}
		i = go_after_pipe(msh->line, i);
	}
	return (1);
}

void	print_cmds(t_msh msh)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("---\n");
	printf("cmd nbr : %d\n", msh.cmd_nbr);
	while (i < msh.cmd_nbr)
	{
		j = 0;
		printf("i = %d\n", i);
		printf("in = %s\n", msh.cmd[i].fd.in_name);
		printf("out = %s\n", msh.cmd[i].fd.out_name);
		while (msh.cmd[i].param[j])
		{
			printf("cmd[%d].param[%d] = %s\n", i, j, msh.cmd[i].param[j]);
			j++;
		}
		printf("------\n");
		i++;
	}
}

void	init_fds(t_msh *msh)
{
	int i;

	i = 0;
	while (i < msh->cmd_nbr)
	{
		msh->cmd[i].fd.in_name = NULL;
		msh->cmd[i].fd.out_name = NULL;
		i++;
	}
}

int	parse_line(t_msh *msh)
{
	msh->cmd_nbr = get_cmd_nbr(msh->line);
	if (!msh->cmd_nbr)
		return (0);	
	msh->cmd = malloc(sizeof(t_cmd) * msh->cmd_nbr);
	if (!msh->cmd)
		return (error_manager(msh, MALLOC_ERR), 1);
	init_fds(msh);
	store_cmds_between_pipes(msh);
	print_cmds(*msh);
	return (1);
}
