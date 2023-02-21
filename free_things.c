/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:57:33 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/21 17:00:42 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_things(t_msh msh)
{
    int i;

    i = 0;
    while (i < msh.cmd_nbr)
		{
			ft_free_tab(msh.cmd[i].param);
			i++;
		}
		free(msh.cmd);
		ft_free_tab(msh.paths);
}