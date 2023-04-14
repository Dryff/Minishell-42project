/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:07:01 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/14 23:55:01 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	g_status = 0;

void	update_msh_status(int status)
{
	g_status = status;
}

int	init_prompt(t_msh *msh)
{
	if (g_status == 0)
		msh->prompt = select_good_prompt_1();
	else
		msh->prompt = select_bad_prompt_1();
	return (0);
}

int	check_builtins(t_msh *msh)
{
	int		i;
	int		j;
	int		flag;
	int 	len;

	i = 0;
	flag = 0;
	while (i < msh->cmd_nbr)
	{
		j = 1;
		if (ft_strlen(msh->cmd[i].param[0]) >= 6)
			len = ft_strlen(msh->cmd[i].param[0]);
		else
			len = 6;
		if (msh->cmd[i].param && msh->cmd[i].param[0] \
		&& !ft_strncmp(msh->cmd[i].param[0], "export", len))
		{
			while (msh->cmd[i].param[j])
			{
				if (valid_export(msh->cmd[i].param[j]) == WRONG_EXPORT)
				{
					update_msh_status(1);
					flag = 1;
					printf("msh: export: '%s': not a valid identifier\n"\
					, msh->cmd[i].param[j]);
				}
				j++;
			}
		}
		i++;
	}
	if (!flag)
		update_msh_status(0);
	return (1);
}

void	main_loop(t_msh *msh)
{
	msh->cmd_nbr = 0;
	if (msh->env.error)
		exit(1);
	set_interactive_signals();
	init_prompt(msh);
	msh->line = readline(msh->prompt);
	if (!msh->line)
		ctrl_d_exit(msh);
	msh->paths = get_paths(msh, msh->env.tab);
	if (check_arrows(msh))
		parse_line(msh);
	if (msh->cmd_nbr && check_builtins(msh))
		commands(msh);
	custom_add_history(msh->line, NOFREE, 0);
	free_things(msh);
	free(msh->line);
}

int	main(int argc, char **argv, char **old_env)
{
	t_msh	msh;

	if (argc != 1)
		return (printf("msh: %s: No such file or directory\n", argv[1]), 1);
	msh.error = 0;
	msh.env = init_env(old_env);
	msh.program_name = argv[0];
	check_env(&msh);
	using_history();
	rl_bind_key('\t', rl_complete);
	while (1)
		main_loop(&msh);
	free_env(&msh);
}
