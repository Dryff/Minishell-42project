/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:01:38 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/10 16:40:18 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*get_expand_cmd(char *str)
{
    return (str + 4);
}

char    *ft_expand(t_env *env, char *cmd)
{
    int i;
    int pos;
    // int size;
    char    *expanded;

    i = 0;
    expanded = NULL;
    while (env->tab[i])
    {
        if (ft_strstr(env->tab[i], cmd))
        {
            if (env->tab[i][0] == cmd[0] && env->tab[i][ft_strlen(cmd)] == '=')
            {
                pos = ft_strlen_until(env->tab[i], '=') + 1;
                expanded = env->tab[i] + pos;
                return (expanded);
            }
        }
        i++;
    }
    return (NULL);
}



////////'ec'"ho" "'l'"