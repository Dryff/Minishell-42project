/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:18:39 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/17 10:13:20 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char    *get_unset_cmd(char *line)
{
    return (line + 6);
}

void    remove_line_from_tab(char **tab, int index)
{
    while (tab[index])
    {
        tab[index] = tab[index + 1];
        index++;
    }
    tab[index - 1] = NULL;
}

int	get_cmd_index(char **tab, char *cmd)
{
    int i;
    int sz;

    i = 0;
    sz = ft_strlen(cmd);
    while (tab[i])
    {
        if (ft_strstr(tab[i], cmd))
        {
            if (tab[i][0] == cmd[0] && (tab[i][sz] == '=' || !tab[i][sz]))
                return (i);
        }
        i++;
    }
    return (-1);
}

void    ft_unset(t_msh *msh, int cmd_id)
{
    int i;
    int j;
    char    *cmd;

    j = 0;
    while (msh->cmd[cmd_id].param[j])
    {
        cmd = msh->cmd[cmd_id].param[j];
        i = get_cmd_index(msh->env.tab, cmd);
        if (i >= 0)
            remove_line_from_tab(msh->env.tab, i);
        i = get_cmd_index(msh->env.sort_tab, cmd);
        if (i >= 0)
            remove_line_from_tab(msh->env.sort_tab, i);
    }
}
