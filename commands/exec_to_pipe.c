/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_to_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:39:11 by colas             #+#    #+#             */
/*   Updated: 2023/04/21 13:50:22 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_op_ip_and_hd(t_msh *msh, int cmd_id, int *fd)
{
	if (msh->cmd[cmd_id].ip.infd >= 1)
	{
		if (dup2(msh->cmd[cmd_id].ip.infd, STDIN_FILENO) == -1)
			exit(1);
		close(msh->cmd[cmd_id].ip.infd);
	}
	else if (msh->cmd[cmd_id].ip.infd == -1)
		exit(1);
	if (msh->cmd[cmd_id].redir_nbr == 0)
	{
		if (cmd_id == msh->cmd_nbr - 1)
		{
			if (dup2(101, STDOUT_FILENO) == -1)
				exit(1);
			close(101);
		}
		if (cmd_id != msh->cmd_nbr - 1)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(1);
			close(fd[1]);
		}
	}
	else if (msh->cmd[cmd_id].op)
	{
		if (dup2(msh->cmd[cmd_id].op[msh->cmd[cmd_id].redir_nbr - 1] \
	.outfd, STDOUT_FILENO) == -1)
			exit(1);
		close(msh->cmd[cmd_id].op[msh->cmd[cmd_id].redir_nbr - 1].outfd);
	}
	return (close(fd[1]), close(100), close(101), 0);
}

void	exec_to_pipe(t_msh *msh, int cmd_id, int *fd)
{
	char	*pathing;
	int		builtin;

	get_op_ip_and_hd(msh, cmd_id, fd);
	builtin = is_builtin(msh->cmd[cmd_id].param[0]);
	if (!builtin && msh->cmd[cmd_id].param[0])
	{
		pathing = get_pathing(*msh, cmd_id);
		if (execve(pathing, msh->cmd[cmd_id].param, msh->env.tab) == -1)
		{
			update_msh_status(127);
			ft_err_printf("msh: %s: command not found\n"\
			, msh->cmd[cmd_id].param[0]);
			free(pathing);
			exit(127);
		}
	}
	else
		exit(exec_builtins(msh, cmd_id, builtin));
}
