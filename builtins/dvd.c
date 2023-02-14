/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:22:55 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/14 11:21:06 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char    *get_dvd_cmd(char *line)
{
    if (ft_strlen(line) == 3)
        return (NULL);
    return (ft_strnstr(line, "dvd", 100) + 4);
}

void    ft_dvd(t_msh *msh, char *cmd)
{
    char    *actual_path;
    char    *new_path;

    (void)msh;
    printf("\ncmd = %s\n", cmd);
    if (!cmd)
    {
        if (chdir(ft_expand(&msh->env, "HOME")) != 0)
        {
            perror("chdir");
            exit(1);
        }
    }
    else
    {
        actual_path = getcwd(NULL, 0);
        new_path = ft_strjoin(actual_path, "/");
        new_path = ft_strjoin(new_path, cmd);
        if (chdir(new_path) != 0)
            perror("chdir");
    }
}

/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file 
*/