/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:09:56 by colas             #+#    #+#             */
/*   Updated: 2023/01/23 10:26:47 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_finder(char **envp)
{
	size_t	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (&envp[i][5]);
}

char	**get_paths(char **envp)
{
	char	*raw_paths;
	char	**paths;

	raw_paths = path_finder(envp);
	paths = ft_split(raw_paths, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

void	exec_to_pipe(t_pipex ppx, char *envp[], int cmd_id, int *fd)
{
	char *pathing;

	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_err_printf("ERROR - 5");
	close(fd[1]);
	pathing = get_pathing(ppx, cmd_id);
	if (execve(pathing, ppx.cmd[cmd_id].param, envp) == -1)
		ft_err_printf("ERROR - 7");
}

void	exec_cmd(t_pipex ppx, char *envp[], int cmd_id)
{
	int	pid;
	int fd[2];

	if (pipe(fd) == -1)
		ft_err_printf("ERROR - 3");
	pid = fork();
	if (pid == -1)
		ft_err_printf("ERROR - 4");
	if (pid == 0)
		exec_to_pipe(ppx, envp, cmd_id, fd);		
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_err_printf("ERROR - 6");
	close(fd[0]);
}

void	exec_last_cmd(t_pipex ppx, char **envp, int cmd_id)
{
	char *pathing;

	if (dup2(ppx.output, STDOUT_FILENO) == -1)
		ft_err_printf("ERROR - 2");
	pathing = get_pathing(ppx, cmd_id);
	if (execve(pathing, ppx.cmd[cmd_id].param, envp) == -1)
		ft_err_printf("ERROR - 7");
}

void test_init_values(t_pipex *ppx)
{
	ppx->infile = 1;
	ppx->outfile = 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	ppx;
	int i;

	if (argc < 2)
		return (ft_err_printf("not good args"), 1);
	ppx.fd_count = 2;
	test_init_values(&ppx);
	ppx.paths = get_paths(envp);
	check_hub(&ppx, argv, argc);
	i = 0;
	if (dup2(ppx.input, STDIN_FILENO) == -1)
			ft_err_printf("ERROR - 1");
	while (i < ppx.cmd_nbr - 1)
		exec_cmd(ppx, envp, i++);
	exec_last_cmd(ppx, envp, i);
	waitpid(-1, NULL, 0);
	return (free_all(ppx.paths), 0);
}
