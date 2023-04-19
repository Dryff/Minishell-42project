/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:53:30 by laquarium         #+#    #+#             */
/*   Updated: 2023/04/19 16:13:51 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	ext_check_built(char **str, int i)
{
	update_msh_status(1);
	ft_err_printf("msh: export: '%s': not a valid identifier\n"\
	, str[i]);
	return (1);
}

int	check_export(char **str)
{
	int		i;
	int		flag;
	
	flag = 0;
	i = 0;
	while (str[i])
	{
		if (valid_export(str[i]) == WRONG_EXPORT)
			flag = ext_check_built(str, i);
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