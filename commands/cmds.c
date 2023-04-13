/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:51:19 by colas             #+#    #+#             */
/*   Updated: 2023/04/13 16:44:50 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	get_op_ip_and_hd(t_msh *msh, int cmd_id, int *fd)
{
	if (msh->cmd[cmd_id].ip.input)
		if (dup2(msh->cmd[cmd_id].ip.infd, STDIN_FILENO) == -1)
			printf("ERROR - yo1\n");
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
	else if (msh->cmd[cmd_id].op)
		if (dup2(msh->cmd[cmd_id].op[msh->cmd[cmd_id].redir_nbr - 1] \
	.outfd, STDOUT_FILENO) == -1)
			printf("ERROR - 5\n");
	close(fd[1]);
}

void	print_something(int nb)
{
	if (nb == SIGQUIT)
	{
		printf("core dumped\n");
		update_msh_status(CTRL_BACKSLASH);
	}
	if (nb == SIGINT)
	{
		printf("\n");
		update_msh_status(CTRL_C);
	}
}

void	run_signal(void)
{
	signal(SIGINT, &no_exec_signal_handler);
	signal(SIGQUIT, &print_something);
}

void	exec_cmd(t_msh *msh, int cmd_id)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		printf("ERROR - 3\n");
	run_signal();
	pid = fork();
	if (pid == -1)
		printf("ERROR - 4\n");
	if (pid == 0)
	{
		// in_exec_signal();
		//signal(SIGINT, &in_exec_signal_handler);
		exec_to_pipe(msh, cmd_id, fd);
	}
	signal(SIGINT, &print_something);
	waitpid(pid, &g_status, 0);
	if (g_status > 255)
		g_status = g_status / 256;
	else
		g_status = g_status % 256;
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		printf("ERROR - 6\n");
	close(fd[0]);
}

void	dup_inffd(int mode)
{
	if (mode == 1)
	{
		if (dup2(STDIN_FILENO, 4095) == -1)
			printf("ERROR - yo2\n");
		if (dup2(STDOUT_FILENO, 4094) == -1)
			printf("ERROR - yo3\n");
	}
	else
	{
		if (dup2(4095, STDIN_FILENO) == -1)
			printf("ERROR - yo4\n");
		if (dup2(4094, STDOUT_FILENO) == -1)
			printf("ERROR - yo5\n");
	}
}

int	check_out(t_msh msh, int i)
{
	int	j;

	j = 0;
	while (j < msh.cmd[i].redir_nbr)
	{
		if (msh.cmd[i].op[j].outfd == -1)
			return (0);
		j++;
	}
	return (1);
}

int	commands(t_msh *msh)
{
	int	i;
	int	builtin;
	int	error;

	dup_inffd(1);
	i = -1;
	error = 0;
	while (++i < msh->cmd_nbr)
	{
		if (msh->cmd[i].param[0] && msh->cmd[i].ip.infd != -1 \
		&& check_out(*msh, i))
		{	
			if (!is_not_builtin_fd(msh, msh->cmd[i].param[0], i))
				exec_cmd(msh, i);
		}
		else
			error = 1;
	}
	builtin = is_builtin(msh->cmd[0].param[0]);
	if (msh->cmd_nbr == 1 && is_not_builtin_fd(msh, msh->cmd[0].param[0], 0))
		exec_builtins(msh, 0, builtin);
	if (error != 0)
		return (0);
	dup_inffd(0);
	return (0);
}
