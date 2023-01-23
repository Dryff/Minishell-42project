/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:08:16 by colas             #+#    #+#             */
/*   Updated: 2023/01/20 15:02:05 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "ft_err_printf/ft_printf.h"
# include "GNL/get_next_line.h"

typedef struct s_args
{
	char	**param;
}				t_args;

typedef struct s_pipex
{
	int		input;
	int		output;
	t_args	*cmd;
	char	**paths;

	int		cmd_nbr;
	int		fd_count;

	int		append_out;
	int		here_doc;

	int		outfile;
	int		infile;
}				t_pipex;

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
void	free_all(char **strs);
char	*ft_ppx_strjoin(char const *s1, char const *s2);
char	*path_finder(char **envp);
void	error_code(char *str);
int		check_hub(t_pipex *pipex, char **argv, int argc);
char	*get_pathing(t_pipex ppx, int j);

#endif