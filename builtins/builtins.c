/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:49:30 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/11 19:45:10 by cgelin           ###   ########.fr       */
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
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (PWD);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (ECHO);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (CD);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (ENV);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (UNSET);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (EXIT);
	return (0);
}

int	is_not_builtin_fd(t_msh *msh, char *cmd, int i)
{
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)) && msh->cmd[i].param[1])
		return (EXPORT);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)) && ft_strncmp(msh->cmd[i].param[1], "-", ft_strlen(msh->cmd[i].param[1])))
		return (CD);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (UNSET);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
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
