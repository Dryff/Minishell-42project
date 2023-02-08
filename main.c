/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:07:01 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/08 11:40:34 by cgelin           ###   ########.fr       */
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

void    ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

int main(int argc, char **argv, char **old_env)
{
    t_msh msh;
    int i;
	(void)argc;
	(void)argv;
    msh.env = init_env(old_env);

    i = 0;
    while (1)
    {
        init_prompt(&msh);
        msh.line = readline(msh.prompt);
	    msh.paths = get_paths(msh.env.tab);
        parse_line(&msh);
	    open_fd(&msh);
        if (!exec_builtin_cmd(&msh))
            commands(&msh);
        while (i < msh.cmd_nbr)
        {
            ft_free_tab(msh.cmd[i].param);
            i++;
        }
        free(msh.cmd);
        ft_free_tab(msh.paths);
        if (!check_exit(msh))
            break;   
    }
}
