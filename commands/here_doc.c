/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:31:40 by colas             #+#    #+#             */
/*   Updated: 2023/04/15 17:44:54 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	ft_putendl_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	write(fd, "\n", 1);
}

void	here_doc_ctrl_c(int nb)
{
	(void)nb;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	update_msh_status(CTRL_C);
}

void	exec_here_doc(t_msh *msh, int cmd_id, int i)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, msh->cmd[cmd_id].ip.here_doc_delim[i]))
			break ;
		if (i == msh->cmd[cmd_id].hd_nbr - 1)
			ft_putendl_fd(line, msh->cmd[cmd_id].ip.infd);
		free(line);
	}
	printf("exiting here_doc\n");
	exit(1);
}

void	develop_here_doc(t_msh *msh)
{
	(void)msh;
}

void	here_doc(t_msh *msh, int cmd_id)
{
	int		i;
	pid_t	pid;

	i = 0;
	printf("hd_nbr = %d\n", msh->cmd[cmd_id].hd_nbr);
	while (i < msh->cmd[cmd_id].hd_nbr)
	{
		pid = fork();
		if (pid == -1)
			return (error_manager(msh, MALLOC_ERR));
		if (pid == 0)
			exec_here_doc(msh, cmd_id, i);
		waitpid(pid, NULL, 0);
		i++;
	}
	develop_here_doc(msh);
	
}
