/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:21:19 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/13 11:26:11 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	custom_add_history(char *line)
{
	static	char	*last;
	int		i;

	i = 0;
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
			return ;
		}
		i++;
	}
}
