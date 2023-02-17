/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:21:19 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/17 08:47:20 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	init_history(void)
{
	rl_bind_key('\t', rl_complete);
	using_history();
}

void    custom_add_history(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
	    return;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			add_history(line);
			return ;
		}
		i++;
	}
}
