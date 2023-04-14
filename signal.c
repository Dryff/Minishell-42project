/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:40:35 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/15 00:19:52 by mfinette         ###   ########.fr       */
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
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, &no_exec_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	backslash_handler(int nb)
{
	if (nb == SIGQUIT)
	{
		// printf("Quit (core dumped)\n");
		update_msh_status(CTRL_BACKSLASH);
	}
	if (nb == SIGINT)
	{
		printf("\n");
		update_msh_status(CTRL_C);
	}
}

void	backslash_print(int nb)
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


/////////////////////////// CAPLU FTW //////////////////////////////


void	handle_interactive_sigquit(int signum, siginfo_t *info, void *context)
{
	(void) signum;
	(void) info;
	(void) context;
}

void	handle_abort_input(int signum, siginfo_t *info, void *context)
{
	(void) signum;
	(void) info;
	(void) context;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	update_msh_status(CTRL_C);
}

void	handle_execution_sigint(int signum, siginfo_t *info, void *context)
{
	(void) signum;
	(void) info;
	(void) context;
	write(1, "\n", 1);
	update_msh_status(CTRL_C);
}

void	handle_execution_sigquit(int signum, siginfo_t *info, void *context)
{
	(void) signum;
	(void) info;
	(void) context;
	printf("Quit (core dumped)\n");
	update_msh_status(CTRL_BACKSLASH);
}

void	set_execution_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	sa.sa_sigaction = handle_execution_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_sigaction = handle_execution_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_interactive_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	sa.sa_sigaction = handle_abort_input;
	sigaction(SIGINT, &sa, NULL);
}