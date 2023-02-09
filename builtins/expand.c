/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:01:38 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/09 10:48:19 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*get_expand_cmd(char *str)
{
    return (str + 4);
}

void	ft_expand(t_env *env, char *cmd)
{
    int i;
    int pos;

    i = 0;
    while (env->tab[i])
    {
        if (ft_strstr(env->tab[i], cmd))
        {
            if (env->tab[i][0] == cmd[0] && env->tab[i][ft_strlen(cmd)] == '=')
            {
                pos = ft_strlen_until(env->tab[i], '=') + 1;
                printf ("%s\n", env->tab[i] + pos);
                return ;
            }
        }
        i++;
    }
    printf("\n");
}



////////'ec'"ho" "'l'"