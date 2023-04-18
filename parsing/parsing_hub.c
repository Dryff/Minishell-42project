/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/18 10:52:37 by mfinette         ###   ########.fr       */
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

void	print_cmds(t_msh msh)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("---\n");
	printf("cmd nbr : %d\n", msh.cmd_nbr);
	printf("--------------------------\n");
	while (i < msh.cmd_nbr)
	{
		printf("(CMD [%d])\n", i);
		j = 0;
		while (msh.cmd[i].ip.in_name[j])
		{
			printf("---INPUT [%d] INFO---\n", j);
			printf("in = %s\n", msh.cmd[i].ip.in_name[j++]);
		}
		if (msh.cmd[i].ip.input)
		{
			printf("input : = %d\n", msh.cmd[i].ip.input);
			printf("infd : = %d\n", msh.cmd[i].ip.infd);
		}
		j = 0;
		while (j < msh.cmd[i].hd_nbr)
		{
			printf("---HD [%d] INFO---\n", j);
			printf("hd = %s\n", msh.cmd[i].ip.here_doc_delim[j++]);
			printf("need develop = %d\n", msh.cmd[i].ip.need_develop);
		}
		j = 0;
		while (j < msh.cmd[i].redir_nbr)
		{
			printf("---OUTPUT [%d] INFO---\n", j);
			printf("out = %s\n", msh.cmd[i].op[j].out_name);
			printf("outfd : %d\n", msh.cmd[i].op[j].outfd);
			printf("output : %d\n", msh.cmd[i].op[j++].output);
		}
		j = 0;
		j = 0;
		printf("---ARGS---\n");
		while (msh.cmd[i].param[j])
		{
			printf("cmd[%d].param[%d] = [%s]\n", i, j, msh.cmd[i].param[j]);
			j++;
		}
		printf("--------------------------\n");
		i++;
	}
	printf("|||||||| RESULT : ||||||||\n");
	printf("--------------------------\n");
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
	// print_cmds(*msh);
	get_and_check_fd(msh);
	return (1);
}
