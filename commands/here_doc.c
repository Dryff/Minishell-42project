/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:31:40 by colas             #+#    #+#             */
/*   Updated: 2023/04/16 22:53:15 by colas            ###   ########.fr       */
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
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	update_msh_status(CTRL_C);
}

void	develop_here_doc_and_write_to_fd(t_msh *msh, char *str, int cmd_id)
{
	t_parse p;
	int useless;

	p.line = str;
	p.i = 0;
	p.strt = 0;
	p.end_q = ft_strlen(p.line);
	useless = 0;
	if (msh->cmd[cmd_id].ip.need_develop)
		p.line = get_dollar(msh, &p, &useless);
	ft_putendl_fd(p.line, msh->cmd[cmd_id].ip.infd);
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
			develop_here_doc_and_write_to_fd(msh, line, cmd_id);
	}
	exit(1);
}

void	here_doc(t_msh *msh, int cmd_id)
{
	int		i;
	pid_t	pid;

	i = 0;
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
}
