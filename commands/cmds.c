/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:51:19 by colas             #+#    #+#             */
/*   Updated: 2023/04/20 15:45:25 by cgelin           ###   ########.fr       */
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
	if (pid != 0 && msh->cmd[cmd_id].param[0] && is_minishell(msh->cmd[cmd_id].param[0], msh->program_name))
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

void	actualize_status(t_msh *msh, int builtin_error)
{
	int	i;

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
	if (builtin_error)
		update_msh_status(1);
	while (i < msh->cmd[msh->cmd_nbr - 1].redir_nbr)
	{
		if (msh->cmd[msh->cmd_nbr - 1].op[i].outfd == -1)
			g_status = 1;
		i++;
	}
}

int	commands(t_msh *msh)
{
	int	i;
	int builtin_error;

	dup_inffd(1);
	i = -1;
	builtin_error = 0;
	if (msh->here_doc_signal == 1)
		return (update_msh_status(CTRL_C), 0);
	while (++i < msh->cmd_nbr)
	{
		if (check_out(*msh, i) && !builtin_work_only_solo(msh, msh->cmd[i].param))
			exec_cmd(msh, i);
		else if (msh->cmd_nbr == 1)
			exec_builtins(msh, i, is_builtin(msh->cmd[i].param[0]));
		else if (builtin_work_only_solo(msh, msh->cmd[i].param))
			builtin_error = display_fake_error(msh->cmd[i].param);
		if (i != msh->cmd_nbr - 1)
			builtin_error = 0;
	}
	while (waitpid(-1, &g_status, 0) > 0)
		;
	actualize_status(msh, builtin_error);
	dup_inffd(0);
	return (0);
}
