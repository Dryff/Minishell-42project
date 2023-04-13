/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:35:31 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/13 21:29:06 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	actually_exit(t_msh *msh, int status, int flag, char *cmd)
{
	update_msh_status(status);
	printf("exit\n");
	if (flag == TOO_MANY)
		printf("msh: exit: too many arguments\n");
	if (flag == NOT_NUMERIC)
		printf("msh: exit: %s: numeric argument required\n", cmd);
	free_things(msh);
	free_env(msh);
	custom_add_history(msh->line, FREE);
	free(msh->line);
	exit(g_status);
}

void	exit_one_parameter(t_msh *msh, char *cmd)
{
	if (ft_str_is_numeric(cmd))
		actually_exit(msh, atoi(cmd), NOFLAG, cmd);
	else
		actually_exit(msh, 2, NOT_NUMERIC, cmd);
}

void	exit_multiple_parameters(t_msh *msh, char *cmd)
{
	update_msh_status(1);
	if (ft_str_is_numeric(cmd))
		printf("exit: too many arguments\n");
	else
		actually_exit(msh, 2, NOT_NUMERIC, cmd);
}

int	ft_exit(t_msh *msh, int cmd_id)
{
	int	i;

	i = 0;
	while (msh->cmd[cmd_id].param[i])
		i++;
	if (i == 1)
		actually_exit(msh, 0, NOFLAG, NULL);
	if (i == 2)
		exit_one_parameter(msh, msh->cmd[cmd_id].param[1]);
	if (i > 2)
		exit_multiple_parameters(msh, msh->cmd[cmd_id].param[1]);
	return (0);
}

void	ctrl_d_exit(t_msh *msh)
{
	printf("exit\n");
	free_env(msh);
	custom_add_history(msh->line, FREE);
	exit(g_status);
}
