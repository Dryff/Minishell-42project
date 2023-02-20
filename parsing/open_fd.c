/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:05:21 by colas             #+#    #+#             */
/*   Updated: 2023/02/20 02:49:20 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_start(t_msh *msh, char c)
{
	int	start;

	start = 0;
	while (msh->line[start] && msh->line[start] != c)
		start++;
	if (msh->line[start])
		start++;
	if (msh->line[start] && msh->line[start] == c)
		start++;
	return (start);
}

void	assign(t_msh *msh, int start, int size, int mode)
{
	if (mode == 0)
		msh->fildes.in_name = ft_substr(msh->line, start, size);
	else
		msh->fildes.out_name = ft_substr(msh->line, start, size);
}

int	get_fd_name(t_msh *msh, char c, int mode)
{
	int	start;
	int	i;
	int	size;
	int	res;

	i = 0;
	size = 0;
	res = 1;
	start = get_start(msh, c);
	if (msh->line[start - 1] && msh->line[start - 1] == c)
		res = 2;
	if (msh->line[start] && !is_delimiter(msh->line[start]))
	{
		while (msh->line[start] && is_white_space(msh->line[start]))
			start++;
		i = start;
		while (msh->line[i] && !is_white_space(msh->line[i]) \
		&& !is_delimiter(msh->line[i]))
		{
			i++;
			size++;
		}
		return (assign(msh, start, size, mode), res);
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
