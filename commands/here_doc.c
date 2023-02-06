/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:31:40 by colas             #+#    #+#             */
/*   Updated: 2023/02/06 18:54:15 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	here_doc(t_msh *msh)
{
	char	*buff;
	int fd;

	fd = open("heredoc_fd", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (!fd)
		return (1);
	while (1)
	{
		buff = readline("> ");
		if (buff == NULL || ft_strncmp(buff, msh->fildes.in_name, ft_strlen(buff)) == 0)
			break ;
		//check les $
		if (write(fd, buff, ft_strlen(buff)) == -1 || write(fd, "\n", 1) == -1)
			return (free(buff), close(fd), 1);
		free(buff);
	}
	return (free(buff), 1);
}