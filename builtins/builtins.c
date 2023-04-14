/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:49:30 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/14 23:24:54 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

#define PWD 1
#define ECHO 2
#define ENV 3
#define CD 4
#define EXPORT 5
#define UNSET 6
#define EXIT 7
#define VAR 8
#define EXPORT_VAR 9

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		cwd_error();
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	is_builtin(char *cmd)
{

	if (cmd == NULL)
		return (0);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	else if (!ft_strcmp(cmd, "cd"))
		return (CD);
	else if (!ft_strcmp(cmd, "env"))
		return (ENV);
	else if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (0);
}

int	is_not_builtin_fd(t_msh *msh, char *cmd, int i)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "export") && msh->cmd[i].param[1])
		return (EXPORT);
	else if (!ft_strcmp(cmd, "cd") && msh->cmd_nbr == 1)
		return (CD);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (0);
}

int	exec_builtins(t_msh *msh, int cmd_id, int builtin)
{
	if (builtin == PWD)
		return (ft_pwd(), 1);
	if (builtin == ECHO)
		return (ft_echo(msh, cmd_id), 1);
	if (builtin == ENV)
		return (ft_print_env(msh), 1);
	if (builtin == CD)
		return (ft_dvd(msh, cmd_id), 1);
	if (builtin == EXPORT)
		return (ft_export(msh, cmd_id), 1);
	if (builtin == UNSET)
		return (ft_unset(msh, cmd_id), 1);
	if (builtin == EXIT)
		return (ft_exit(msh, cmd_id), 1);
	if (builtin == VAR)
		return (ft_print_status(), 1);
	return (0);
}
