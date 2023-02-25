/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:37:28 by colas             #+#    #+#             */
/*   Updated: 2023/02/25 23:43:44 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void check_input(t_msh *msh)
{
	if (msh->fildes.input == 1)
		msh->fildes.infd = open(msh->fildes.in_name, O_RDONLY);
	if (msh->fildes.infd == -1)
	{
		if (access(msh->fildes.in_name, F_OK) == 0)
			ft_err_printf("msh: permission denied: %s\n", \
			msh->fildes.in_name);
		else
			ft_err_printf("msh: no such file or directory: %s\n", \
			msh->fildes.in_name);
		return;
	}
}

void check_output(t_msh *msh)
{
	if (msh->fildes.output == 1)
		msh->fildes.outfd = open(msh->fildes.out_name, \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (msh->fildes.output == 2)
		msh->fildes.outfd = open(msh->fildes.out_name, \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	if (msh->fildes.outfd == -1)
	{
		ft_err_printf("msh: permission denied: %s\n", msh->fildes.out_name);
		return;
	}
}

int get_and_check_fd(t_msh *msh)
{
	check_input(msh);
	check_output(msh);
	return (1);
}
