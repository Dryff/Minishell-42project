/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_check_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:37:28 by colas             #+#    #+#             */
/*   Updated: 2023/03/27 10:27:18 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	check_input(t_msh *msh, int cmd_id)
{
	if (msh->cmd[cmd_id].fd.input == 1)
		msh->cmd[cmd_id].fd.infd = open(msh->cmd[cmd_id].fd.in_name, O_RDONLY);
	if (msh->cmd[cmd_id].fd.infd == -1)
	{
		if (access(msh->cmd[cmd_id].fd.in_name, F_OK) == 0)
			ft_err_printf("msh: permission denied: %s\n", \
			msh->cmd[cmd_id].fd.in_name);
		else
			ft_err_printf("msh: no such file or directory: %s\n", \
			msh->cmd[cmd_id].fd.in_name);
	}
	if (msh->cmd[cmd_id].fd.input)
		free(msh->cmd[cmd_id].fd.in_name);
}

void	check_output(t_msh *msh, int cmd_id)
{
	if (msh->cmd[cmd_id].fd.output == 1)
		msh->cmd[cmd_id].fd.outfd = open(msh->cmd[cmd_id].fd.out_name, \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (msh->cmd[cmd_id].fd.output == 2)
		msh->cmd[cmd_id].fd.outfd = open(msh->cmd[cmd_id].fd.out_name, \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	if (msh->cmd[cmd_id].fd.outfd == -1)
	{
		ft_err_printf("msh: permission denied: %s\n", msh->cmd[cmd_id].fd.out_name);
		return ;
	}
	if (msh->cmd[cmd_id].fd.output)
		free(msh->cmd[cmd_id].fd.out_name);
}

int	get_and_check_fd(t_msh *msh)
{
	int i;

	i = 0;
	while (i < msh->cmd_nbr)
	{
		check_input(msh, i);
		check_output(msh, i);
		i++;
	}
	
	return (1);
}
