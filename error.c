/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:09:00 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/13 16:47:25 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	error_manager(t_msh *msh, int err_num)
{
	(void)msh;
	if (err_num == MALLOC_ERR)
		return (printf("Malloc error, stopping the program.\n"), exit(1));
}
