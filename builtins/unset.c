/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:18:39 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/09 11:24:21 by mfinette         ###   ########.fr       */
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

void    ft_unset(t_env *env, char *cmd)
{
    int i;

    i = get_cmd_index(env->tab, cmd);
    if (i >= 0)
        remove_line_from_tab(env->tab, i);
    i = get_cmd_index(env->sort_tab, cmd);
    if (i >= 0)
        remove_line_from_tab(env->sort_tab, i);
}
