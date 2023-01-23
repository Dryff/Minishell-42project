/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:47:10 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/23 11:33:59 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char	**tab;
	int		size;
}				t_env;

typedef struct s_msh
{
	t_env	env;
	char	*prompt;
	char	*line;
}				t_msh;

/* Minishell */
int		minishell(t_msh *msh);
void	export_var(t_env *env, char *cmd);

/* Env */
t_env	init_env(char **envp);

/* Utils */
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strstr(const char *str, const char *to_find);


#endif