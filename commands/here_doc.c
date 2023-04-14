/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:31:40 by colas             #+#    #+#             */
/*   Updated: 2023/04/15 01:24:43 by mfinette         ###   ########.fr       */
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

void	here_doc(t_msh *msh, int cmd_id)
{
	char	*line;
	int		i;
	int		dup;

	i = 0;
	dup = g_status;
	while (i < msh->cmd[cmd_id].hd_nbr)
	{
		while (dup == g_status)
		{
			signal(SIGINT, &here_doc_ctrl_c);
			line = readline("> ");
			if (!line)
				break ;
			// len = ft_strlen(msh->cmd[cmd_id].ip.here_doc_delim[i]);
			// if (len < (int)ft_strlen(line))
			// 	len = ft_strlen(line);
			if (!ft_strcmp(line, msh->cmd[cmd_id].ip.here_doc_delim[i]))
				break ;
			if (i == msh->cmd[cmd_id].hd_nbr - 1)
				ft_putendl_fd(line, msh->cmd[cmd_id].ip.infd);
			free(line);
		}
		i++;
	}
}
