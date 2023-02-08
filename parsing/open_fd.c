/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:05:21 by colas             #+#    #+#             */
/*   Updated: 2023/02/08 11:45:33 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_fd_name(t_msh *msh, char c, int mode)
{
	int start;
	int i;
	int size;
	int res;

	start = 0;
	i = 0;
	size = 0;
	res = 1;
	while (msh->line[start] && msh->line[start] != c)
		start++;
	if (msh->line[start])
		start++;
	if (msh->line[start] && msh->line[start] == c)
	{
		res = 2;
		start++;
	}
	if (msh->line[start] && !is_delimiter(msh->line[start]))
	{
		while (msh->line[start] && is_white_space(msh->line[start]))
			start++;
		i = start;
		while (msh->line[i] && !is_white_space(msh->line[i]) && !is_delimiter(msh->line[i]))
		{
			i++;
			size++;
		}
		if (mode == 0)
			msh->fildes.in_name = ft_substr(msh->line, start, size);
		else
			msh->fildes.out_name = ft_substr(msh->line, start, size);
		return (res);
	}
	return (0);
}

int	open_fd(t_msh *msh)
{
	msh->fildes.input = get_fd_name(msh, '<', 0);
	msh->fildes.output = get_fd_name(msh, '>', 1);
	msh->fildes.infd = 0;
	msh->fildes.outfd = 0;
	check_hub(msh);
	if (msh->fildes.input == 2)
		here_doc(msh);
	return (0);
}