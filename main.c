/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:07:01 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/12 16:19:55 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int msh_status = 0;

void update_msh_status(int status)
{
	msh_status = status;
}

int init_prompt(t_msh *msh)
{
	if (msh_status == 0)
		msh->prompt = select_good_prompt_1();
	else
		msh->prompt = select_bad_prompt_1();
	return (0);
}

int check_exit(t_msh msh)
{
	if (ft_strncmp(msh.line, "exit", 4) == 0)
		return (0);
	return (1);
}

void ft_print_status(void)
{
	printf("%d\n", msh_status);
}

int check_builtins(t_msh *msh)
{
	int i;
	int j;
	char **cmd;

	i = 0;
	while (i < msh->cmd_nbr)
	{
		cmd = msh->cmd[i].param;
		j = 1;
		if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
		{
			while (cmd[j])
			{
				if (valid_export(cmd[j]) == 2)
				{
					printf("msh: export: '%s': not a valid identifier\n", cmd[j]);
					if (msh->cmd_nbr == 1)
					{
						update_msh_status(1);
						return (1);
					}
				}
				j++;
			}
		}
		i++;
	}
	return (1);
}

int main(int argc, char **argv, char **old_env)
{
	t_msh msh;

	(void)argc;
	(void)argv;
	msh.error = 0;
	msh.env = init_env(old_env);
	check_env(&msh);
	while (1)
	{
		msh.cmd_nbr = 0;
		if (msh.env.error)
			exit(1);
		init_signals_history();
		init_prompt(&msh);
		msh.line = readline(msh.prompt);
		if (!msh.line)
			actually_exit(&msh, 0);
		if (!ft_strncmp(msh.line, "\n", ft_strlen(msh.line)))
		{
			msh_status = 0;
			continue;
		}
		msh.paths = get_paths(msh.env.tab);
		if (check_arrows(&msh))
			parse_line(&msh);
		if (msh.cmd_nbr && check_builtins(&msh))
			commands(&msh);
		custom_add_history(msh.line);
		free_things(&msh);
		free(msh.line);
	}
	free_env(msh);
}
