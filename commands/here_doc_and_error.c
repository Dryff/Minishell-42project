/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_and_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:31:40 by colas             #+#    #+#             */
/*   Updated: 2023/03/16 16:23:05 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	error_print(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			printf("msh : %s: No such file or directory\n", cmd);
			break ;
		}
		i++;
	}
	if (i == ft_strlen(cmd))
		ft_err_printf("msh: command not found : %s\n", \
		cmd);
	return (0);
}

// int	here_doc(t_msh *msh)
// {
// 	char	*buff;

// 	msh->fildes.heredoc_fd = open("heredoc_fd", O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	if (!msh->fildes.heredoc_fd)
// 		return (1);
// 	while (1)
// 	{
// 		printf("%s|", msh->fildes.in_name);
// 		buff = readline("> ");
// 		if (buff == NULL || ft_strncmp(buff, msh->fildes.in_name, ft_strlen(msh->fildes.in_name)) == 0)
// 			break ;
// 		//check les $
// 		if (write(msh->fildes.heredoc_fd, buff, ft_strlen(buff)) == -1 || write(msh->fildes.heredoc_fd, "\n", 1) == -1)
// 			return (free(buff), close(msh->fildes.heredoc_fd), 1);
// 		free(buff);
// 	}
// 	return (free(buff), 1);
// }
