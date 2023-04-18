/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:51:19 by colas             #+#    #+#             */
/*   Updated: 2023/04/18 16:27:16 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

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
	if (pid != 0 && is_minishell(msh->cmd[cmd_id].param[0], msh->program_name))
		ignore_signals();
	if (pid == 0)
		exec_to_pipe(msh, cmd_id, fd);
	signal(SIGQUIT, SIG_IGN);
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

void	check_redir_to_status(t_msh *msh)
{
	int i;

	i = 0;
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
	{
		if (WTERMSIG(g_status) == 13)
			g_status = 0;
		else
		g_status = 128 + WTERMSIG(g_status);
	}
	while (i < msh->cmd[msh->cmd_nbr - 1].redir_nbr)
	{
		if (msh->cmd[msh->cmd_nbr - 1].op[i].outfd == -1)
			g_status = 1;
		i++;
	}
}

int	commands(t_msh *msh, int error)
{
	int	i;
	int	builtin;

	dup_inffd(1);
	i = -1;
	if (msh->here_doc_signal == 1)
		return (update_msh_status(CTRL_C), 0);
	while (++i < msh->cmd_nbr)
	{
		if (msh->cmd[i].param[0] && check_out(*msh, i))
		{
			if (is_builtin_fd(msh, msh->cmd[i].param[0]))
				exec_cmd(msh, i);
		}
		else
			error = 1;
	}
	while (waitpid(-1, &g_status, 0) > 0)
		;
	check_redir_to_status(msh);
	builtin = is_builtin(msh->cmd[0].param[0]);
	if (msh->cmd[0].param[0] && msh->cmd_nbr == 1 && \
	is_builtin(msh->cmd[0].param[0]))
		exec_builtins(msh, 0, builtin, EXEC);
	return (dup_inffd(0), 0);
}
