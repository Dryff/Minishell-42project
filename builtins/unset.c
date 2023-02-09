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

void    ft_unset(t_env *env, char *cmd)
{
    (void)env;
    (void)cmd;
}

char    *get_unset_cmd(char *line)
{
    return (line + 4);
}