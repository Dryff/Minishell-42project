/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laquarium <laquarium@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:57:33 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/30 18:22:04 by laquarium        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_free_tab(char **tab)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (tab[j])
		j++;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_things(t_msh *msh)
{
    int i;
	int j;

	j = 0;
	i = 0;
	while (i < msh->cmd_nbr)
	{
		ft_free_tab(msh->cmd[i].param);
		while (j < msh->cmd[i].redir_nbr)
		{
			free(msh->cmd[i].op[j].out_name);
			j++;
		}
		free(msh->cmd[i].op);
		i++;
	}
	if (msh->cmd_nbr)
		free(msh->cmd);
	if (msh->paths)
		ft_free_tab(msh->paths);
}
