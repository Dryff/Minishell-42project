/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:09:00 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/18 11:33:45 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	error_manager(t_msh *msh, int err_num)
{
	(void)msh;
	if (err_num == MALLOC_ERR)
		return (ft_err_printf("Malloc error, stopping the program.\n"), exit(1));
}
