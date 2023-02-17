/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:51:19 by colas             #+#    #+#             */
/*   Updated: 2023/02/17 10:06:57 by cgelin           ###   ########.fr       */
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
			printf("Command not found : %s\n", msh->cmd[cmd_id].param[0]);
	}
	// exec_builtins(msh, msh->cmd[cmd_id].param);
}

void	exec_cmd(t_msh *msh, int cmd_id)
{
	int	pid;
	int fd[2];

	if (pipe(fd) == -1)
		printf("ERROR - 3\n");
	pid = fork();
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
	char *pathing;
	int	builtin;
	
	if (msh->fildes.output)
		if (dup2(msh->fildes.outfd, STDOUT_FILENO) == -1)
			printf("ERROR - 2\n");
	builtin = is_builtin(msh->cmd[cmd_id].param[0]);
	if (!builtin)
	{
		pathing = get_pathing(*msh, cmd_id);
		if (execve(pathing, msh->cmd[cmd_id].param, msh->env.tab) == -1)
			printf("Command not found : %s\n", msh->cmd[cmd_id].param[0]);
	}
	exec_builtins(msh, cmd_id, builtin);
}

void	dup_inffd(t_msh *msh)
{
	if (msh->fildes.input == 1)
	{
		if (dup2(STDIN_FILENO, 4095) == -1)
			printf("ERROR - yo\n");
		if (dup2(msh->fildes.infd, STDIN_FILENO) == -1)
			printf("ERROR - 1\n");
	}
	if (msh->fildes.input == 2)
	{
		if (dup2(STDIN_FILENO, 4095) == -1)
			printf("ERROR - yo\n");
		if (dup2(msh->fildes.heredoc_fd, STDIN_FILENO) == -1)
			printf("ERROR - 1\n");
	}
}

int commands(t_msh *msh)
{
	int i;
	
	// dprintf(2, "input : %d\n", msh->fildes.input);
	// dprintf(2, "infd : %d\n", msh->fildes.infd);
	// dprintf(2, "output : %d\n", msh->fildes.output);
	// dprintf(2, "outfd : %d\n", msh->fildes.outfd);
	// dprintf(2, "heredoc_fd : %d\n", msh->fildes.heredoc_fd);
	dup_inffd(msh);
	msh->pid = fork();
	if (msh->pid == -1)
		printf("ERROR - 12\n");
	i = 0;
	if (msh->pid == 0)
	{	
		while (i < msh->cmd_nbr - 1)
			exec_cmd(msh, i++);
		exec_last_cmd(msh, i);
	}
	waitpid(msh->pid, NULL, 0);
	if (msh->fildes.input == 1 || msh->fildes.input == 2)
		if (dup2(4095, STDIN_FILENO) == -1)
				printf("ERROR - yo\n");
	return (0);
}