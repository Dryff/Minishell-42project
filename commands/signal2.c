/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 01:30:58 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/20 17:22:12 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	backslash_print(int nb)
{
	if (nb == SIGQUIT)
	{
		ft_err_printf("Quit (core dumped)\n");
		update_msh_status(CTRL_BACKSLASH);
	}
	if (nb == SIGINT)
	{
		printf("\n");
		update_msh_status(CTRL_C);
	}
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	cwd_error(void)
{
	ft_err_printf("msh: cd: sorry I don't know where I am. ");
	ft_err_printf("To return to the last existing directory, use cd -\n");
	update_msh_status(1);
}

void	here_doc_sigint(int nb)
{
	(void)nb;
	write(1, "\n", 1);
	update_msh_status(CTRL_C);
	exit(CTRL_C);
}
