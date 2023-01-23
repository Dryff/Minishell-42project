/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 14:33:41 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/20 14:50:03 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_the_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = backup[i];
		i++;
	}
	return (line[i] = '\0', line);
}

int	check_end_of_line(char *backup, int read_res)
{
	int	i;

	i = 0;
	if (read_res == 0)
		return (1);
	if (!backup)
		return (0);
	while (backup[i] != '\0')
	{
		if (backup[i] == '\n')
			return (1);
			i++;
	}
	return (0);
}

char	*read_file(int fd, char *backup)
{
	char	*buffer;
	int		read_res;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_res = 1;
	while (!check_end_of_line(backup, read_res))
	{
		read_res = read(fd, buffer, BUFFER_SIZE);
		if (read_res < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_res] = '\0';
		backup = ft_strjoin(backup, buffer);
	}
	free(buffer);
	return (backup);
}

char	*get_next_buffer(char *buffer)
{
	int		i;
	int		n;
	char	*next_line_start;

	i = 0;
	n = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next_line_start = malloc(sizeof(char) * (ft_gnl_strlen(buffer) - i + 1));
	if (!next_line_start)
		return (NULL);
	n = 0;
	i++;
	while (buffer[i])
		next_line_start[n++] = buffer[i++];
	if (buffer)
		next_line_start[n] = '\0';
	free(buffer);
	return (next_line_start);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (free(buffer), buffer = NULL, NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = get_the_line(buffer);
	buffer = get_next_buffer(buffer);
	return (line);
}
