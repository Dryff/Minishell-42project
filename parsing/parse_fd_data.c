/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fd_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:05:21 by colas             #+#    #+#             */
/*   Updated: 2023/03/20 16:44:49 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int get_start_of_fd_name(t_msh *msh, char c, int *res)
{
	int start;

	start = 0;
	while (msh->line[start] && msh->line[start] != c)
		start++;
	if (msh->line[start])
		start++;
	if (msh->line[start] && msh->line[start] == c)
	{
		*res = 2;
		start++;
	}
	return (start);
}

void get_names(t_msh *msh, int start, int size, int mode)
{
	if (mode == 0)
		msh->fildes.in_name = ft_substr(msh->line, start, size);
	else
		msh->fildes.out_name = ft_substr(msh->line, start, size);
}

int get_fd_name(t_msh *msh, char c, int mode)
{
	int start;
	int i;
	int size;
	int res;

	i = 0;
	size = 0;
	res = 1;
	start = get_start_of_fd_name(msh, c, &res);
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
		return (get_names(msh, start, size, mode), res);
	}
	return (0);
}

int open_fd(t_msh *msh)
{
	if (msh->fildes.input >= 0)
		msh->fildes.input = get_fd_name(msh, '<', 0);
	else
		msh->fildes.input = 0;
	if (msh->fildes.output >= 0)
		msh->fildes.output = get_fd_name(msh, '>', 1);
	else
		msh->fildes.output = 0;
	msh->fildes.infd = 0;
	msh->fildes.outfd = 0;
	if (msh->fildes.input || msh->fildes.output)
		get_and_check_fd(msh);
	return (0);
}

int parse_fd_data(t_msh *msh)
{
	//si ya pas des trucs bizarre genre >>>> ou <<<<<< ou >>>> 
	/*->*/open_fd(msh);
	return (0);
}
