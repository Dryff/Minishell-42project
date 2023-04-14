/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:21:19 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/14 23:55:14 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#define FREE 0
#define NOFREE 1

void	custom_add_history(char *line, int status, int i)
{
	static char	*last;

	if (status == FREE)
	{
		free (last);
		return ;
	}
	if (ft_strlen(line) == 0)
		return ;
	if (!last)
		last = ft_strdup("");
	while (line[i])
	{
		if (line[i] != ' ' && ft_strcmp(line, last) != 0)
		{
			add_history(line);
			free(last);
			last = ft_strdup(line);
			if (!last)
				exit(1);
			return ;
		}
		i++;
	}
}
