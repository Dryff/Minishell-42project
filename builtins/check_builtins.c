/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laquarium <laquarium@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:53:30 by laquarium         #+#    #+#             */
/*   Updated: 2023/04/18 15:46:19 by laquarium        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	ext_check_built(t_msh *msh, int i, int j)
{
	update_msh_status(1);
	ft_err_printf("msh: export: '%s': not a valid identifier\n"\
	, msh->cmd[i].param[j]);
	return (1);
}

int	check_builtins(t_msh *msh)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	while (i < msh->cmd_nbr)
	{
		j = 1;
		if (msh->cmd[i].param && msh->cmd[i].param[0] \
		&& !ft_strcmp(msh->cmd[i].param[0], "export"))
		{
			while (msh->cmd[i].param[j])
			{
				if (valid_export(msh->cmd[i].param[j]) == WRONG_EXPORT)
					flag = ext_check_built(msh, i, j);
				j++;
			}
		}
		i++;
	}
	if (!flag)
		update_msh_status(0);
	return (1);
}

int check_exit(t_msh *msh)
{
    int     len;
    char    **cmd;
    int     i;

    i = 0;
    while (i < msh->cmd_nbr)
    {
        cmd = msh->cmd[i].param;
        len = tab_len(cmd);
        if (cmd[0] && !ft_strcmp(cmd[0], "exit"))
        {
            if (len == 2)
            {
                if (!ft_str_is_numeric(cmd[1]))
                    return (ft_err_printf("msh: exit: %s: numeric argument required\n", cmd[1]), 0);
            }
            if (len > 2)
            {
                if (!ft_str_is_numeric(cmd[1]))
                    return (ft_err_printf("msh: exit: %s: numeric argument required\n", cmd[1]), 0);
                else
                    return (ft_err_printf("msh: exit: too many arguments\n", 0));
            }
        }
        i++;
    }
    return (0);
}