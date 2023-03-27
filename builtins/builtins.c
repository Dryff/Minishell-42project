/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:49:30 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/19 17:11:21 by mfinette         ###   ########.fr       */
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

int ft_exit(void)
{
	printf("exit\n");
	exit(0);
    return (0);
}

int	ft_echo(t_msh *msh, int cmd_id)
{
	int		i;
	int		arg_nbr;
	char	*cmd;

	cmd = msh->cmd[cmd_id].param[1];
	if (!cmd)
	{
		printf("\n");
		return (0);
	}
	i = 1;
	if ((cmd[0] == '-' && !cmd[1]) \
			|| (cmd[0] == '-' && cmd[1] == 'n'))
		i = 2;
	arg_nbr = 0;
	while (msh->cmd[cmd_id].param[arg_nbr])
		arg_nbr++;
	while (msh->cmd[cmd_id].param[i])
	{
		printf("%s", msh->cmd[cmd_id].param[i]);
		if (i != arg_nbr - 1)
			printf(" ");
		i++;
	}
	if (!(cmd[0] == '-' && cmd[1] == 'n'))
		printf("\n");
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 3))
		return (PWD);
	else if (!ft_strncmp(cmd, "echo", 4))
		return (ECHO);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (CD);
	else if (!ft_strncmp(cmd, "env", 3))
		return (ENV);
	else if (!ft_strncmp(cmd, "export", 6))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (UNSET);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (EXIT);
	else if (!ft_strncmp(cmd, "var", 3))
		return (VAR);
	return (0);
}

int	is_not_builtin_fd(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 6))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (CD);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (UNSET);
	else if (!ft_strncmp(cmd, "exit", 4))
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
		return (ft_exit(), 1);
	if (builtin == VAR)
		return (ft_print_status(), 1);
	return (0);
}
