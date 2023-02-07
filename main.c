/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:07:01 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/07 15:39:46 by colas            ###   ########.fr       */
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
    int i;

    i = 0;
	(void)argc;
	(void)argv;
    msh.env = init_env(old_env);
    while (1)
    {
        init_prompt(&msh);
        msh.line = readline(msh.prompt);
	    msh.paths = get_paths(msh.env.tab);
        parse_line(&msh);
	    open_fd(&msh);
        if (!exec_builtin_cmd(&msh))
            commands(&msh);
        if (!check_exit(msh))
            break;   
    }
}
