/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_check_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:37:28 by colas             #+#    #+#             */
/*   Updated: 2023/04/10 19:27:01 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	hd_exec(t_msh *msh, int cmd_id)
{
	if (msh->cmd[cmd_id].hd_nbr)
	{
		msh->cmd[cmd_id].ip.infd = open("hd_tmp", \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
		here_doc(msh, cmd_id);
		close(msh->cmd[cmd_id].ip.infd);
		msh->cmd[cmd_id].ip.infd = open("hd_tmp", O_RDONLY);
	}
}

int	check_input(t_msh *msh, int cmd_id)
{
	if (msh->cmd[cmd_id].ip.input == 1)
		msh->cmd[cmd_id].ip.infd = open(msh->cmd[cmd_id].ip.in_name, O_RDONLY);
	if (msh->cmd[cmd_id].ip.infd == -1 && msh->cmd[cmd_id].ip.input == 1)
	{
		if (access(msh->cmd[cmd_id].ip.in_name, F_OK) == 0)
			return (ft_err_printf("msh: %s: Permission denied\n", \
			msh->cmd[cmd_id].ip.in_name), msh_status = 1, 0);
		else
			return (ft_err_printf("msh: %s: No such file or directory\n", \
			msh->cmd[cmd_id].ip.in_name), msh_status = 1, 0);
	}
	return (1);
}

int	check_output(t_msh *msh, int cmd_id, int op_id)
{
	if (msh->cmd[cmd_id].op[op_id].output == 1)
		msh->cmd[cmd_id].op[op_id].outfd = \
		open(msh->cmd[cmd_id].op[op_id].out_name, \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (msh->cmd[cmd_id].op[op_id].output == 2)
		msh->cmd[cmd_id].op[op_id].outfd = \
		open(msh->cmd[cmd_id].op[op_id].out_name, \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	if (msh->cmd[cmd_id].op[op_id].outfd == -1)
	{
		ft_err_printf("msh: permission denied: %s\n", \
		msh->cmd[cmd_id].op[op_id].out_name);
		msh_status = 1;
		return (0);
	}
	return (1);
}

int	get_and_check_fd(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	while (i < msh->cmd_nbr)
	{
		hd_exec(msh, i);
		if (!check_input(msh, i))
			break ;
		j = 0;
		while (j < msh->cmd[i].redir_nbr)
		{
			if (!check_output(msh, i, j))
				break ;
			j++;
		}
		i++;
	}
	return (1);
}
