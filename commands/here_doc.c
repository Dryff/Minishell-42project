/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:31:40 by colas             #+#    #+#             */
/*   Updated: 2023/04/05 09:52:48 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	ft_putendl_fd(char *str, int fd)
{
	int i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	write(fd, "\n", 1);
}

void	here_doc(t_msh *msh, int cmd_id, int fd)
{
	char	*line;
	// pid_t 	pid;
	int 	i;

	i = 0;
	while (i < msh->cmd[cmd_id].hd_nbr)
	{
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (ft_strncmp(line, msh->cmd[cmd_id].ip.here_doc_delim[i], \
						ft_strlen(line)) == 0)
				break ;
			ft_putendl_fd(line, fd);
			free(line);
		}
		i++;
	}
}
