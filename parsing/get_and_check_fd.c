/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_check_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:37:28 by colas             #+#    #+#             */
/*   Updated: 2023/03/27 20:15:08 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	check_input(t_msh *msh, int cmd_id)
{
	if (msh->cmd[cmd_id].ip.input == 1)
		msh->cmd[cmd_id].ip.infd = open(msh->cmd[cmd_id].ip.in_name, O_RDONLY);
	if (msh->cmd[cmd_id].ip.infd == -1)
	{
		if (access(msh->cmd[cmd_id].ip.in_name, F_OK) == 0)
			ft_err_printf("msh: permission denied: %s\n", \
			msh->cmd[cmd_id].ip.in_name);
		else
			ft_err_printf("msh: no such file or directory: %s\n", \
			msh->cmd[cmd_id].ip.in_name);
	}
	if (msh->cmd[cmd_id].ip.input)
		free(msh->cmd[cmd_id].ip.in_name);
}

void	check_output(t_msh *msh, int cmd_id, int op_id)
{
	if (msh->cmd[cmd_id].op[op_id].output == 1)
		msh->cmd[cmd_id].op[op_id].outfd = \
		open(msh->cmd[cmd_id].op[op_id].out_name,\
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (msh->cmd[cmd_id].op[op_id].output == 2)
		msh->cmd[cmd_id].op[op_id].outfd = \
		open(msh->cmd[cmd_id].op[op_id].out_name, \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	if (msh->cmd[cmd_id].op[op_id].outfd == -1)
	{
		ft_err_printf("msh: permission denied: %s\n", \
		msh->cmd[cmd_id].op[op_id].out_name);
		return ;
	}
}

int	get_and_check_fd(t_msh *msh)
{
	int i;
	int j;

	i = 0;
	while (i < msh->cmd_nbr)
	{
		check_input(msh, i);
		j = 0;
		printf("%dbjr\n", msh->cmd[i].redir_nbr);
		while (j < msh->cmd[i].redir_nbr)
		{
			check_output(msh, i, j);
			j++;
		}
		i++;
	}
	return (1);
}
