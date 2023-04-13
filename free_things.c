/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:57:33 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/13 22:03:08 by mfinette         ###   ########.fr       */
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

void	free_things(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < msh->cmd_nbr)
	{
		free_more_things(msh, i);
		i++;
	}
	if (msh->cmd_nbr)
		free(msh->cmd);
	if (msh->paths)
		ft_free_tab(msh->paths);
}

void	free_more_things(t_msh *msh, int i)
{
	int	j;

	j = 0;
	ft_free_tab(msh->cmd[i].param);
	while (j < msh->cmd[i].redir_nbr)
	{
		free(msh->cmd[i].op[j].out_name);
		j++;
	}
	j = 0;
	if (!msh->cmd[i].hd_nbr)
		free(msh->cmd[i].ip.in_name);
	while (j < msh->cmd[i].hd_nbr)
	{
		free(msh->cmd[i].ip.here_doc_delim[j]);
		j++;
	}
	free(msh->cmd[i].ip.here_doc_delim);
	free(msh->cmd[i].op);
}
