/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 01:30:58 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/15 01:47:55 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

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

void	enable_minishell_signals(void)
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
