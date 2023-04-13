/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:40:35 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/13 16:49:43 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	no_exec_signal_handler(int signal_num)
{
	if (signal_num == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		update_msh_status(CTRL_C);
		rl_redisplay();
	}
}

void	init_signals_history(void)
{

	signal(SIGINT, &no_exec_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	in_exec_signal_handler(int signal_num)
{
	printf("here\n");
	if (signal_num == SIGQUIT)
	{
		printf("core dumped\n");
		update_msh_status(CTRL_BACKSLASH);
		// actually_exit(3);
	}
	if (signal_num == SIGINT)
	{
		printf("here\n");
		update_msh_status(CTRL_C);
		// actually_exit(3);
	}
}
