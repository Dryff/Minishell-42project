/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:47:10 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/14 23:31:14 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "ft_err_printf/ft_printf.h"
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include "emoji.h"

// ERROR CODES //
# define MALLOC_ERR 1

// RETURN VALUES //
# define NT_VALID_ID 1
# define SYNTAX_ERROR 2
# define IS_DIRECTORY 126
# define PERM_DENIED 126
# define CMD_NT_FND 127
# define CTRL_C 130
# define CTRL_SLASH 131
# define CTRL_BACKSLASH 131

// CD //
# define OLD 1
# define HOME 2

// EXIT HISTORY //
# define FREE 0
# define NOFREE 1

// ACTUALLY EXIT //
# define NOFLAG 0
# define TOO_MANY 1
# define NOT_NUMERIC 2

// EXPORT //
# define VALID_EXPORT 1
# define WRONG_EXPORT 2
# define EMPTY_EXPORT 3
# define EXISTING_EXPORT 4
# define PLUS_EXPORT 5

// PARSING ERROR //
# define ERR_MESS "msh: syntax error near unexpected token"

extern int	g_status;

typedef struct s_env
{
	char	**tab;
	char	**sort_tab;
	int		error;
}				t_env;

typedef struct s_outputs
{
	int		outfd;
	int		output;
	char	*out_name;
}				t_outputs;

typedef struct s_inputs
{
	int		input;
	int		infd;
	char	*in_name;
	char	**here_doc_delim;
}				t_inputs;

typedef struct s_cmd
{
	char		**param;
	int			hd_nbr;
	int			hd_id;
	int			hd_tmp;
	int			redir_nbr;
	t_outputs	*op;
	t_inputs	ip;
}				t_cmd;

typedef struct s_parse
{
	int		i;
	int		end_q;
	int		strt;
	int		arg_sz;
	char	q;
	char	*line;
}				t_parse;

typedef struct s_msh
{
	t_env		env;
	t_cmd		*cmd;
	int			redir_id;
	int			cmd_nbr;
	int			pid;
	int			error;
	int			status;
	char		**paths;
	char		**historic;
	char		*prompt;
	char		*line;
	char		*ex_val;
	char		*program_name;
}				t_msh;

/* Minishell */
int			minishell(t_msh *msh);
void		free_things(t_msh *msh);
void		free_more_things(t_msh *msh, int i);
void		error_manager(t_msh *msh, int err_num);
void		ft_print_status(void);
void		update_msh_status(int status);

/* DVD*/
char		*get_dvd_cmd(char *line);
void		ft_dvd(t_msh *msh, int cmd_id);
void		chdir_home_old(t_msh *msh, int code);
void		update_old_pwd(t_msh *msh, char *actual_path);
void		cwd_error(void);

/* HISTORIC */
void		init_history(void);
void		custom_add_history(char *line, int status);

/* EXIT */
int			ft_exit(t_msh *msh, int cmd_id);
void		actually_exit(t_msh *msh, int status, int flag, char *cmd);
void		ctrl_d_exit(t_msh *msh);

/* EMOJI */
char		*select_good_prompt_1(void);
char		*select_good_prompt_2(void);
char		*select_bad_prompt_1(void);
char		*select_bad_prompt_2(void);

/* Env */
t_env		init_env(char **envp);
void		ft_print_env(t_msh *msh);
void		ft_declare_print(t_env *env);
char		*get_export_cmd(char *line);
int			ft_export(t_msh *msh, int cmd_id);
int			*ft_bool_strnstr(const char *haystack, const char *needle, \
size_t len);
char		**add_comand_to_tab(char **tab, char *cmd);
char		**envp_dup(char **tab);
void		free_env(t_msh *msh);
char		**init_secret_env(char **envp);
void		update_SHLVL(t_msh *msh);
void		check_env(t_msh *msh);
void		check_shlvl(t_msh *msh);
void		check_pwd(t_msh *msh);
void		reset_shlvl(t_msh *msh, int shlvl);
int			is_valid_c(char c);

/* Export*/
void		add_export(t_msh *msh, char *cmd);
void		add_invisible_export(t_msh *msh, char *cmd);
void		replace_export(t_msh *msh, char *cmd, int pos);
int			get_position(char **tab, char *cmd);
void		ft_export_print(char *str);
void		ft_strswap(char **str1, char **str2);
int			ft_strcmp(char *s1, char *s2);
void		replace_secret_export(t_msh *msh, char *cmd, int index);
int			complete_export(t_msh *msh, char *cmd);
int			valid_export(char *cmd);

/* UNSET attention ca va chauffer sa mere*/
char		*get_unset_cmd(char *line);
void		ft_unset(t_msh *msh, int cmd_id);

/* Expand */
char		*ft_expand(t_env *env, char *cmd);
char		*ft_expand_tab(char **tab, char *cmd);
char		*get_expand_cmd(char *str);

/* builtins */
int			exec_builtin_cmd(t_msh *msh);
int			is_builtin(char *cmd);
int			is_not_builtin_fd(t_msh *msh, char *cmd, int i);
int			exec_builtins(t_msh *msh, int cmd_id, int builtin);
int			ft_echo(t_msh *msh, int cmd_id);

/* signal */
void		in_exec_signal_handler(int signal_num);
void		init_signals(void);
void		reset_default_signal(void);
void		in_exec_signal(void);
void		no_exec_signal_handler(int signal_num);
void		child_signal(void);
void		backslash_handler(int nb);
void		only_update_signal(int nb);
void		backslash_print(int nb);
void		set_interactive_signals(void);
void		set_execution_signals(void);

/* exec */
void		exec_to_pipe(t_msh *msh, int cmd_id, int *fd);
void		get_op_ip_and_hd(t_msh *msh, int cmd_id, int *fd);

/* Cmd_utils */
char		*ft_strchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_strstr(const char *str, const char *to_find);
char		*ft_strjoin(char const *s1, char const *s2);
int			commands(t_msh *msh);
char		**get_paths(t_msh *msh, char **envp);
char		*get_pathing(t_msh msh, int j);
void		here_doc(t_msh *msh, int cmd_id);
char		*ft_itoa(int n);

/* Msh_utils */
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
void		free_all(char **strs);

/* Parsing */
int			parse_line(t_msh *msh);
int			get_cmd_nbr(char *str);
int			ft_is_ascii(char c);
int			open_fd(t_msh *msh);
int			check_fd(t_msh *msh, int i, int j);
int			get_quote(char *s, int i);
int			is_in_quote(char *s, int *start_quote, int i, int is_in_quotes);
int			get_and_check_fd(t_msh *msh);
char		*replace_env_arg(t_msh *msh, t_parse *p, int *cursor, int mode);
int			is_end_of_arg(int i, char *line, char q, int s);
char		*quotes_dollars_and_redir(t_msh *msh, char *sub, int j);
char		*get_dollar(t_msh *msh, t_parse *p, int *has_dollar);
char		*getline_rm_quote(t_msh *msh, t_parse p);
int			quote_rm_nbr(t_parse p);
char		*replace_spaces(t_parse p, char *line);
char		*replace_spaces_of_expanded(t_parse p, char *line);
int			go_to_end_quote(t_parse p, int i, char *line);
int			parse_fd_data(t_msh *msh);
int			is_alpha(char c);
void		quote_handling(t_msh *msh, t_parse *p);
int			check_arrows(t_msh *msh);
char		*develop_name(t_msh *msh, char *sub, int hd);
t_outputs	*get_op_array(t_msh *msh, char *str, int cmd_id);
char		**get_hd_array(t_msh *msh, char *str, int cmd_id);
int			is_name_before_arrow(t_msh *msh, t_parse p);
int			get_size_until_arrow(t_msh *msh, int i);
void		get_redir(t_msh *msh, t_parse *p, int cmd_index);
int			quote_check(char *str, int i, int *start_quote, int *is_in_quotes);
int			go_after_pipe(char *line, int i);
char		*get_expanded(t_msh *msh, t_parse *p, int cursor);
void		actualize_ind(t_parse *p, char *expanded, char *str, int in_q);
void		secure(t_parse *p);

/* Basic utils */
char		**ft_split(char const *str, char c);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *src);
int			ft_strlen_until(char *str, char c);
int			is_in_charset(char c, char *str);
void		sort_tab(t_env *env);
char		**tab_dup(char **tab);
void		free_tab(char **tab);
int			tab_len(char **tab);
int			ft_str_is_numeric(char *str);
int			is_alpha(char c);
int			is_num(char c);

/* Parse_utils */
int			is_delimiter(char c);
int			is_white_space(char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			get_cmd_size(char *s, int i);
int			is_end_quote(char *str, int start_quote, int i);
int			get_size(char *s, int i);
char		*ft_strjoin_by_sep(char const *s1, char const *s2);

#endif
