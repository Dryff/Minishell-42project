/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:18:39 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/12 16:00:01 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*get_unset_cmd(char *line)
{
	return (line + 6);
}

void	remove_line_from_tab(char **tab, int index)
{
	int	i;

	i = 0;
	while (tab[index])
	{
		if (i == 0)
			free(tab[index]);
		tab[index] = tab[index + 1];
		index++;
		i++;
	}
	tab[index - 1] = NULL;
}

int	get_cmd_index(char **tab, char *cmd)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strstr(tab[i], cmd))
		{
			if (tab[i][0] == cmd[0])
				return (i);
		}
		i++;
	}
	return (-1);
}

void	ft_unset(t_msh *msh, int cmd_id)
{
	int		i;
	int		j;
	char	*cmd;

	j = 1;
	while (msh->cmd[cmd_id].param[j])
	{
		cmd = msh->cmd[cmd_id].param[j];
		i = get_cmd_index(msh->env.tab, cmd);
		if (i >= 0)
			remove_line_from_tab(msh->env.tab, i);
		i = get_cmd_index(msh->env.sort_tab, cmd);
		if (i >= 0)
			remove_line_from_tab(msh->env.sort_tab, i);
		j++;
	}
	update_msh_status(0);
}
