/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:35:31 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/12 16:20:56 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"


int ft_str_is_numeric(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

void    actually_exit(t_msh *msh, int status)
{
    update_msh_status(status);
    printf("exit\n");
    free_things(msh);
	free(msh->line);
    exit(msh_status);
}

int ft_exit(t_msh *msh, int cmd_id)
{
    int i;

    i = 0;
    while (msh->cmd[cmd_id].param[i])
        i++;
    if (i == 1)
        actually_exit(msh, 0);
    if (i ==2)
    {
        if (ft_str_is_numeric(msh->cmd[cmd_id].param[1]))
            actually_exit(msh, atoi(msh->cmd[cmd_id].param[1]));
        else
        {
            printf("exit: %s: numeric argument required\n", msh->cmd[cmd_id].param[1]);
            actually_exit(msh, 2);
        }
    }
    if (i > 2)
    {
        update_msh_status(1);
        if (ft_str_is_numeric(msh->cmd[cmd_id].param[1]))
            printf("exit: too many arguments\n");
        else
        {
            printf("exit: %s: numeric argument required\n", msh->cmd[cmd_id].param[1]);
            actually_exit(msh, 2);
        }
    }
    update_msh_status(0);
    return (0);
}
