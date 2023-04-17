/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:51:19 by colas             #+#    #+#             */
/*   Updated: 2023/04/17 11:00:43 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	get_op_ip_and_hd(t_msh *msh, int cmd_id, int *fd)
{
	if (msh->cmd[cmd_id].ip.input)
		if (dup2(msh->cmd[cmd_id].ip.infd, STDIN_FILENO) == -1)
			exit(1);
	close(fd[0]);
	if (msh->cmd[cmd_id].redir_nbr == 0)
	{
		if (cmd_id == msh->cmd_nbr - 1)
		{
			if (dup2(101, STDOUT_FILENO) == -1)
				exit(1);
		}
		else
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(1);
	}
	else if (msh->cmd[cmd_id].op)
		if (dup2(msh->cmd[cmd_id].op[msh->cmd[cmd_id].redir_nbr - 1] \
	.outfd, STDOUT_FILENO) == -1)
			exit(1);
	close(fd[1]);
	close(100);
	close(101);
}

void	exec_cmd(t_msh *msh, int cmd_id)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	set_execution_signals();
	if (pid == -1)
		exit(1);
	if (pid != 0 && ft_strcmp(msh->cmd[cmd_id].param[0], \
	msh->program_name) == 0)
		enable_minishell_signals();
	if (pid == 0)
		exec_to_pipe(msh, cmd_id, fd);
	waitpid(pid, &g_status, 0);
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
		g_status = 128 + WTERMSIG(g_status);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(1);
	close(fd[0]);
}

void	dup_inffd(int mode)
{
	if (mode == 1)
	{
		if (dup2(STDIN_FILENO, 100) == -1)
			exit(1);
		if (dup2(STDOUT_FILENO, 101) == -1)
			exit(1);
	}
	else
	{
		if (dup2(100, STDIN_FILENO) == -1)
			exit(1);
		if (dup2(101, STDOUT_FILENO) == -1)
			exit(1);
		close(100);
		close(101);
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

int	commands(t_msh *msh, int error)
{
	int	i;
	int	builtin;

	dup_inffd(1);
	i = -1;
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
	if (msh->cmd[0].param[0] && msh->cmd_nbr == 1 && \
	is_not_builtin_fd(msh, msh->cmd[0].param[0], 0))
		exec_builtins(msh, 0, builtin);
	if (error != 0)
		return (0);
	dup_inffd(0);
	return (0);
}
