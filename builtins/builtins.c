/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:49:30 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/17 09:08:24 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	ft_echo(t_msh *msh, int cmd_id)
{
	int		i;
	int		arg_nbr;
	char	*cmd;

	cmd = msh->cmd[cmd_id].param[1];
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

int is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4))
		return (2);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (3);
	else if (!ft_strncmp(cmd, "export", 6))
		return (4);
	else if (!ft_strncmp(cmd, "env", 2))
		return (5);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (6);
	return (0);
}

int	exec_builtins(t_msh msh, int cmd_id, int builtin)
{
    printf("builtin : %d\n", builtin);
	if (builtin == 1)
		return (ft_pwd(), 1);
	if (builtin == 2)
		return (ft_echo(&msh, cmd_id), 1);
	if (builtin == 3)
		return (ft_dvd(&msh, cmd_id), 1);
	if (builtin == 4)
		return (ft_export(&msh, cmd_id), 1);
	return (0);
	// if (builtin == 5)
	// 	return (ft_unset(&msh->env, get_unset_cmd(msh->line)), 1);
	// if (builtin == 6)
	// 	return (ft_expand(&msh->env, get_expand_cmd(msh->line)), 1);
}

// int	exec_builtin_cmd(t_msh *msh)
// {
// 	if (search_cmd(msh->line, "pwd"))
// 		return (ft_pwd(), 1);
// 	else if (search_cmd(msh->line, "echo"))
// 	{	
// 		if (search_cmd(msh->line, "-n"))
// 			return (ft_echo(msh, 0), 1);
// 		else
// 			return (ft_echo(msh, 1), 1);
// 	}
// 	else if (search_cmd(msh->line, "dvd"))
// 		return (ft_dvd(msh, get_dvd_cmd(msh->line)), 1);
// 	else if (search_cmd(msh->line, "export"))
// 		return (ft_export(&msh->env, get_export_cmd(msh->line)), 1);
// 	else if (search_cmd(msh->line, "unset"))
// 		return (ft_unset(&msh->env, get_unset_cmd(msh->line)), 1);
// 	else if (search_cmd(msh->line, "var"))
// 		return (ft_expand(&msh->env, get_expand_cmd(msh->line)), 1);
// 	return (0);
// }
