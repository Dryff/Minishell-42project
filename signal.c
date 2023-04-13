/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:40:35 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/13 22:21:55 by mfinette         ###   ########.fr       */
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

void	init_signals(void)
{
	signal(SIGINT, &no_exec_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	backslash_handler(int nb)
{
	if (nb == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		update_msh_status(CTRL_BACKSLASH);
	}
	if (nb == SIGINT)
	{
		printf("\n");
		update_msh_status(CTRL_C);
	}
}

void	child_signal(void)
{
	signal(SIGQUIT, &backslash_handler);
}

void	only_update_signal(int nb)
{
	if (nb == SIGINT)
		update_msh_status(CTRL_C);
	if (nb == SIGQUIT)
		update_msh_status(CTRL_BACKSLASH);
}
