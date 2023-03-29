/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:51:19 by colas             #+#    #+#             */
/*   Updated: 2023/03/29 10:18:06 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	exec_to_pipe(t_msh *msh, int cmd_id, int *fd)
{
	char	*pathing;
	int		builtin;

	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		printf("ERROR - 5\n");
	close(fd[1]);
	builtin = is_builtin(msh->cmd[cmd_id].param[0]);
	if (!builtin)
	{
		pathing = get_pathing(*msh, cmd_id);
		if (execve(pathing, msh->cmd[cmd_id].param, msh->env.tab) == -1)
		{
			update_msh_status(1);
			perror(msh->cmd[cmd_id].param[0]);
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

void	exec_last_cmd(t_msh *msh, int cmd_id)
{
	char	*pathing;
	int		pid;
	int		builtin;

	pid = fork();
	reset_default_signal();
	if (pid == -1)
		printf("ERROR - fork\n");
	if (pid == 0)
	{
		builtin = is_builtin(msh->cmd[cmd_id].param[0]);
		if (!builtin)
		{
			pathing = get_pathing(*msh, cmd_id);
			if (execve(pathing, msh->cmd[cmd_id].param, msh->env.tab) == -1)
			{
				update_msh_status(1);
				ft_err_printf("msh: command not found : %s\n"\
				, msh->cmd[cmd_id].param[0]);
				free(pathing);
			}
		}
		else
			exec_builtins(msh, cmd_id, builtin);
		exit(1);
	}
}

void	dup_inffd(t_msh *msh)
{
	if (dup2(STDIN_FILENO, 4095) == -1)
		printf("ERROR - yo\n");
}

// dprintf(2, "input : %d\n", msh->fildes.input);
// dprintf(2, "infd : %d\n", msh->fildes.infd);
// dprintf(2, "output : %d\n", msh->fildes.output);
// dprintf(2, "outfd : %s\n", msh->fildes.outfd);
// dprintf(2, "heredoc_fd : %d\n", msh->fildes.heredoc_fd);

int	commands(t_msh *msh)
{
	int	i;
	int	builtin;

	dup_inffd(msh);
	i = 0;
	while (i < msh->cmd_nbr - 1)
	{
		if (msh->cmd[i].param[0])
			if (!is_not_builtin_fd(msh->cmd[i].param[0]))
				exec_cmd(msh, i);
		i++;
	}
	if (!msh->cmd[i].param[0])
		return (0);
	builtin = is_builtin(msh->cmd[i].param[0]);
	if (!is_not_builtin_fd(msh->cmd[i].param[0]))
		exec_last_cmd(msh, i);
	else if (msh->cmd_nbr == 1 && is_not_builtin_fd(msh->cmd[i].param[0]))
		exec_builtins(msh, i, builtin);
	waitpid(-1, NULL, 0);
	if (dup2(4095, STDIN_FILENO) == -1)
		printf("ERROR - yo\n");
	return (0);
}
