/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:49:30 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/21 11:12:19 by cgelin           ###   ########.fr       */
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
		update_msh_status(1);
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
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	return (0);
}

int	builtin_work_only_solo(t_msh *msh, char **cmd)
{
	(void)msh;
	if (cmd[0] == NULL)
		return (0);
	if (!ft_strcmp(cmd[0], "export") && cmd[1])
		return (1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd") && msh->cmd_nbr == 1)
		return (1);
	return (0);
}

int	display_fake_error(char **str)
{
	if (!ft_strcmp(str[0], "export"))
		return (check_export(str));
	else if (!ft_strcmp(str[0], "exit"))
		return (check_exit(str));
	else if (!ft_strcmp(str[0], "cd"))
		return (check_exit(str));
	return (0);
}

int	exec_builtins(t_msh *msh, int cmd_id, int builtin)
{
	if (builtin == PWD)
		return (ft_pwd());
	if (builtin == ECHO)
		return (ft_echo(msh, cmd_id), 0);
	if (builtin == ENV)
		return (ft_print_env(msh), 0);
	if (builtin == CD)
		return (ft_dvd(msh, cmd_id));
	if (builtin == EXPORT)
		return (ft_export(msh, cmd_id));
	if (builtin == UNSET && msh->cmd_nbr == 1)
		return (ft_unset(msh, cmd_id), 0);
	if (builtin == EXIT && msh->cmd_nbr == 1)
		return (ft_exit(msh, cmd_id));
	if (builtin == EXIT)
		return (check_exit(msh->cmd[cmd_id].param));
	return (0);
}
