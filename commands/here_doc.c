/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:31:40 by colas             #+#    #+#             */
/*   Updated: 2023/04/08 15:46:14 by colas            ###   ########.fr       */
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

void	here_doc(t_msh *msh, int cmd_id)
{
	char	*line;
	int 	i;
	int len;

	i = 0;
	while (i < msh->cmd[cmd_id].hd_nbr)
	{
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			len = ft_strlen(msh->cmd[cmd_id].ip.here_doc_delim[i]);
			if (len < (int)ft_strlen(line))
				len = ft_strlen(line);
			if (!ft_strncmp(line, msh->cmd[cmd_id].ip.here_doc_delim[i], len))
				break ;
			if (i == msh->cmd[cmd_id].hd_nbr - 1)
				ft_putendl_fd(line, msh->cmd[cmd_id].ip.infd);
			free(line);
		}
		i++;
	}
}
