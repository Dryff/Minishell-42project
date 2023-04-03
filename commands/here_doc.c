/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:31:40 by colas             #+#    #+#             */
/*   Updated: 2023/04/03 09:49:43 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	ft_putendl_fd(char *str, int fd)
{
	int i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	write (fd, "\n", 1);
}

void	here_doc(t_msh *msh, int cmd_id, int fd)
{
	char	*line;
	int i;

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
