/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:47:10 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/28 19:15:11 by cgelin           ###   ########.fr       */
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

typedef struct s_cmd
{
	char	**param;
}				t_cmd;

typedef struct s_env
{
	char	**tab;
	char	**sort_tab;
	int		sort_size;
	int		size;
}				t_env;

typedef struct s_msh
{
	t_env	env;
	t_cmd	*cmd;
	int		cmd_nbr;
	char	*prompt;
	char	*line;
}				t_msh;

/* Minishell */
int		minishell(t_msh *msh);

/* Env */
t_env	init_env(char **envp);
void	ft_print_env(t_msh *msh);
void	ft_declare_print(t_env *env);
char	*get_export_cmd(char *line);
int		ft_export(t_env *env, char *cmd);
int		*ft_bool_strnstr(const char *haystack, const char *needle, size_t len);

/* Cmd_utils */
int		search_cmd(const char *hs, const char *nee);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strstr(const char *str, const char *to_find);

/* Msh_utils */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	free_all(char **strs);

/* Parsing */
int		parse_line(t_msh *msh);

/* Basic utils */
char	**ft_split(char const *str, char c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *src);
int		ft_strlen_until(char *str, char c);
int		is_in_charset(char c, char *str);
void	sort_tab(t_env *env);
char	**tab_dup(char **tab);
void	free_tab(char **tab);


/* Parse_utils */
int		is_delimiter(char *str, int i);
int		is_white_space(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		get_size(char *s, int i);
char	*ft_strjoin(char const *s1, char const *s2);


#endif