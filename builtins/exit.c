/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:35:31 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/20 16:48:40 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	actually_exit(t_msh *msh, int status, int flag, char *cmd)
{
	update_msh_status(status);
	printf("exit\n");
	if (flag == TOO_MANY)
		ft_err_printf("msh: exit: too many arguments\n");
	if (flag == NOT_NUMERIC)
		ft_err_printf("msh: exit: %s: numeric argument required\n", cmd);
	free_things(msh);
	free_env(msh);
	custom_add_history(msh->line, FREE, 0);
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

int	exit_multiple_parameters(t_msh *msh, char *cmd)
{
	update_msh_status(1);
	if (ft_str_is_numeric(cmd))
	{	
		ft_err_printf("exit: too many arguments\n");
		return (1);
	}
	else
		actually_exit(msh, 2, NOT_NUMERIC, cmd);
	return (0);
}

int	ft_exit(t_msh *msh, int cmd_id)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (msh->cmd[cmd_id].param[i])
		i++;
	if (i == 1)
		actually_exit(msh, 0, NOFLAG, NULL);
	if (i == 2)
		exit_one_parameter(msh, msh->cmd[cmd_id].param[1]);
	if (i > 2)
		res = exit_multiple_parameters(msh, msh->cmd[cmd_id].param[1]);
	return (res);
}

void	ctrl_d_exit(t_msh *msh)
{
	printf("exit\n");
	free_env(msh);
	custom_add_history(msh->line, FREE, 0);
	exit(g_status);
}
