/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/03 18:50:42 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	get_cmd_place_i_after_pipe(t_msh *msh, int *i, int j)
{
	char	*cmd;
	char	*sub;
	int 	size;

	size = get_size(msh->line, *i);
	if (check_fd(msh, *i, j))
	{
		if (is_name_before_arrow(msh, *i))
			size = get_size_until_arrow(msh, *i);
		else
			*i = get_cmd_is_after_arrow(msh, *i);
	}
	sub = ft_substr(msh->line, *i, size);
	printf("size = %d\n", size);
	printf("cmd = %s\n", sub);
	cmd = rm_quotes(*msh, sub);
	msh->cmd[j].param = ft_split(cmd, 10);
	*i += get_size(msh->line, *i);
	free(cmd);
}

int	go_to_arg_start(char *line, int i)
{
	while (line[i] && is_white_space(line[i]))
		i++;
	return (i);
}

int	store_cmds_between_pipes(t_msh *msh, t_parse *p)
{
	int		i;
	int		j;

	(void)p;
	i = 0;
	j = 0;
	while (msh->line[i])
	{
		i = go_to_arg_start(msh->line, i);
		if (msh->line[i])
		{
			get_cmd_place_i_after_pipe(msh, &i, j);
			j++;
		}
		i++;
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
		printf("heredoc[%d] = %d\n",i, msh.cmd[i].here_doc);
		while (msh.cmd[i].param[j])
		{
			printf("cmd[%d].param[%d] = %s\n", i, j, msh.cmd[i].param[j]);
			j++;
		}
		printf("------\n");
		i++;
	}
}

int	parse_line(t_msh *msh)
{
	t_parse *p;

	p = NULL;
	msh->cmd_nbr = get_cmd_nbr(msh->line);
	if (!msh->cmd_nbr)
		return (0);
	msh->cmd = malloc(sizeof(t_cmd) * msh->cmd_nbr);
	if (!msh->cmd)
		return (0);
	store_cmds_between_pipes(msh, p);
	print_cmds(*msh);
	return (1);
}
