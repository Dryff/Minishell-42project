/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:07:01 by mfinette          #+#    #+#             */
/*   Updated: 2023/01/23 11:36:36 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	init_prompt(t_msh *msh)
{
    msh->prompt = "msh -> ";
    return (0);
}

int check_exit(t_msh msh)
{
    if (ft_strncmp(msh.line, "exit", 4) == 0) 
        return (0);
    return (1);
}

int main(int argc, char **argv, char **old_env)
{
    t_msh msh;
    t_env env;
    
    // env = init_env(old_env);
    // export_var(&env, argv[1]);
    
    // msh.env = init_env(old_env);
    while (1)
    {
        init_prompt(&msh);
        msh.line = readline(msh.prompt);
        minishell(&msh);
        if (!check_exit(msh))
            break;   
    }
}

