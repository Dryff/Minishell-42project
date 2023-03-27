/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:40:35 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/27 13:11:48 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"


void	in_exec_signal_handler(int signal_num)
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
	struct sigaction	sa;

	using_history();
	rl_bind_key('\t', rl_complete);
	sa.sa_handler = in_exec_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	reset_default_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
