/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 02:03:35 by colas             #+#    #+#             */
/*   Updated: 2023/02/20 02:14:13 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_cmd_nbr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_white_space(str[i]))
			count = 1;
		i++;
	}
	i = 0;
	while (str[i])
	{	
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

int	go_after_fd_name(t_msh *msh, int i)
{
	if (msh->line[i] == '>' || msh->line[i] == '<')
	{
		while (msh->line[i] && is_delimiter(msh->line[i]))
			i++;
		while (msh->line[i] && (is_white_space(msh->line[i]) \
					|| is_delimiter(msh->line[i])))
			i++;
		while (msh->line[i] && !is_white_space(msh->line[i]) \
				&& !is_delimiter(msh->line[i]))
			i++;
	}
	return (i);
}
