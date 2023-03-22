/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:07:01 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/21 19:27:34 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <signal.h>

int	msh_status = 0;

void	update_msh_status(int status)
{
	msh_status = status;
}

int	init_prompt(t_msh *msh)
{
	if (msh_status == 0)
		msh->prompt = "\e[0;32mmsh -> \e[0m";
	else
		msh->prompt = "\e[0;31mmsh -> \e[0m";
	return (0);
}

int	check_exit(t_msh msh)
{
	if (ft_strncmp(msh.line, "exit", 4) == 0)
		return (0);
	return (1);
}

void signal_handler(int signal_num)
{
	if (signal_num == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void ft_print_status(void)
{
	printf("%d\n", msh_status);
}

int	main(int argc, char **argv, char **old_env)
{
	t_msh	msh;

	(void)argc;
	(void)argv;
	msh.env = init_env(old_env);
	while (1)
	{
		init_signals_history();
		init_prompt(&msh);
		update_msh_status(0);
		msh.line = readline(msh.prompt);
		if (!msh.line)
		{
			printf("exit\n");
			exit(1);
		}
		msh.paths = get_paths(msh.env.tab);
		parse_line(&msh);
		parse_fd_data(&msh);
		if (msh.cmd_nbr)
			commands(&msh);
		custom_add_history(msh.line);
		free_things(&msh);
		if (!check_exit(msh))
			exit(1);
		free(msh.line);
	}
	free_env(msh);
}
