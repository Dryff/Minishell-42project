/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:31:40 by colas             #+#    #+#             */
/*   Updated: 2023/04/20 16:58:10 by cgelin           ###   ########.fr       */
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

void	develop_here_doc_and_write_to_fd(t_msh *msh, char *str, int cmd_id)
{
	t_parse	p;
	int		useless;

	p.line = str;
	p.i = 0;
	p.strt = 0;
	p.end_q = ft_strlen(p.line);
	useless = 0;
	if (msh->cmd[cmd_id].ip.need_develop)
		p.line = get_dollar(msh, &p, &useless);
	ft_putendl_fd(p.line, msh->cmd[cmd_id].ip.infd);
	if (msh->cmd[cmd_id].ip.need_develop)
		free(p.line);
}

void	exec_here_doc(t_msh *msh, int cmd_id, int i)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_status == CTRL_C)
			exit (CTRL_C);
		if (!line)
			break ;
		if (!ft_strcmp(line, msh->cmd[cmd_id].ip.here_doc_delim[i]))
			break ;
		if (i == msh->cmd[cmd_id].hd_nbr - 1)
			develop_here_doc_and_write_to_fd(msh, line, cmd_id);
	}
	exit(0);
}

void	here_doc(t_msh *msh, int cmd_id)
{
	int		i;
	pid_t	pid;

	i = 0;
	msh->here_doc_signal = 0;
	ignore_signals();
	while (i < msh->cmd[cmd_id].hd_nbr)
	{
		if (msh->here_doc_signal == 1)
			break ;
		pid = fork();
		if (pid == -1)
			return (error_manager(msh, MALLOC_ERR));
		if (pid == 0)
		{
			signal(SIGINT, here_doc_sigint);
			exec_here_doc(msh, cmd_id, i);
		}
		waitpid(pid, &g_status, 0);
		if (g_status == 33280)
			msh->here_doc_signal = 1;
		i++;
	}	
}
