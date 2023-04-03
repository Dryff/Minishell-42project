/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:51:19 by colas             #+#    #+#             */
/*   Updated: 2023/04/03 15:13:41 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	get_op_ip_and_hd(t_msh *msh, int cmd_id, int *fd)
{

	if (msh->cmd[cmd_id].ip.input == 1)
		if (dup2(msh->cmd[cmd_id].ip.infd, STDIN_FILENO) == -1)
			printf("ERROR - yo1\n");
	// if (msh->cmd[cmd_id].ip.input == 2)
	// {
	// 	here_doc(msh, cmd_id, fd[0]);
	// 	if (dup2(fd[0], STDIN_FILENO) == -1)
	// 		printf("ERROR - yo12\n");
	// }
	close(fd[0]);
	if (msh->cmd[cmd_id].redir_nbr == 0)
	{
		if (cmd_id == msh->cmd_nbr - 1)
		{
			if (dup2(4094, STDOUT_FILENO) == -1)
				printf("ERROR - 5\n");
		}
		else
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				printf("ERROR - 5\n");
	}
	else if (dup2(msh->cmd[cmd_id].op[msh->cmd[cmd_id].redir_nbr - 1] \
	.outfd, STDOUT_FILENO) == -1)
		printf("ERROR - 5\n");
	close(fd[1]);
}

void	exec_to_pipe(t_msh *msh, int cmd_id, int *fd)
{
	char	*pathing;
	int		builtin;
	
	get_op_ip_and_hd(msh, cmd_id, fd);
	builtin = is_builtin(msh->cmd[cmd_id].param[0]);
	if (!builtin)
	{
		pathing = get_pathing(*msh, cmd_id);
		if (execve(pathing, msh->cmd[cmd_id].param, msh->env.tab) == -1)
		{
			update_msh_status(1);
			ft_err_printf("msh: %s: command not found\n"\
			, msh->cmd[cmd_id].param[0]);
			free(pathing);
		}
	}
	else
		exec_builtins(msh, cmd_id, builtin);
	exit(1);
}

void	exec_cmd(t_msh *msh, int cmd_id)
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		printf("ERROR - 3\n");
	pid = fork();
	reset_default_signal();
	if (pid == -1)
		printf("ERROR - 4\n");
	if (pid == 0)
		exec_to_pipe(msh, cmd_id, fd);
	waitpid(pid, NULL, 0);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		printf("ERROR - 6\n");
	close(fd[0]);
}

void	dup_inffd(void)
{
	if (dup2(STDIN_FILENO, 4095) == -1)
		printf("ERROR - yo2\n");
	if (dup2(STDOUT_FILENO, 4094) == -1)
		printf("ERROR - yo3\n");
}

int	commands(t_msh *msh)
{
	int	i;
	int	builtin;

	dup_inffd();
	i = 0;
	while (i < msh->cmd_nbr)
	{
		if (msh->cmd[i].param[0] && msh->cmd[i].ip.infd != -1)
			if (!is_not_builtin_fd(msh->cmd[i].param[0]))
				exec_cmd(msh, i);
		i++;
	}
	if (msh->cmd_nbr == 1 && is_not_builtin_fd(msh->cmd[0].param[0]))
	{
		builtin = is_builtin(msh->cmd[0].param[0]);
		exec_builtins(msh, 0, builtin);
	}
	waitpid(-1, NULL, 0);
	if (dup2(4095, STDIN_FILENO) == -1)
		printf("ERROR - yo4\n");
	if (dup2(4094, STDOUT_FILENO) == -1)
		printf("ERROR - yo5\n");
	return (0);
}
