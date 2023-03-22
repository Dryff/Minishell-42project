/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:09:00 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/22 20:58:54 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void    error_manager(t_msh *msh, int err_num)
{
    if (err_num == MALLOC_ERR)
        return (printf("Malloc error, stopping the program.\n"), exit(1));
}