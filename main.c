/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laquarium <laquarium@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:07:01 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/18 15:17:43 by laquarium        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	g_status = 0;

int	init_prompt(t_msh *msh)
{
	if (g_status == 0)
		msh->prompt = select_good_prompt_1();
	else
		msh->prompt = select_bad_prompt_1();
	return (0);
}

void	main_loop(t_msh *msh)
{
	msh->cmd_nbr = 0;
	msh->here_doc_signal = 0;
	if (msh->env.error)
		exit(1);
	set_interactive_signals();
	init_prompt(msh);
	msh->line = readline(msh->prompt);
	if (!msh->line)
		ctrl_d_exit(msh);
	msh->paths = get_paths(msh, msh->env.tab);
	if (check_arrows(msh, 0))
		parse_line(msh);
	if (msh->cmd_nbr && check_builtins(msh))
	{
		check_exit(msh);
		commands(msh, 0);
	}
	custom_add_history(msh->line, NOFREE, 0);
	free_things(msh);
	free(msh->line);
}

int	main(int argc, char **argv, char **old_env)
{
	t_msh	msh;

	if (argc != 1)
		return (ft_err_printf("msh: %s: No such file or directory\n", \
		argv[1]), 1);
	msh.error = 0;
	msh.env = init_env(old_env);
	if (msh.env.error)
		error_manager(&msh, 1);
	msh.program_name = argv[0];
	check_env(&msh);
	using_history();
	rl_bind_key('\t', rl_complete);
	while (1)
		main_loop(&msh);
	free_env(&msh);
}
