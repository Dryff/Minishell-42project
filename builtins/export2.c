/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:45:07 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/16 13:25:42 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	add_export(t_msh *msh, char *cmd)
{
	char	**dup;

	dup = add_comand_to_tab(msh->env.tab, cmd);
	if (!dup)
		return ;
	free(msh->env.tab);
	msh->env.tab = tab_dup(dup);
	sort_tab(&msh->env);
}

void	add_invisible_export(t_msh *msh, char *cmd)
{
	char	**dup;

	printf("(ADD)cmd = %s\n", cmd);
	printf("get_pos = %d\n", get_position(msh->env.sort_tab, cmd));
	if (get_position(msh->env.sort_tab, cmd) < 0)
	{
		dup = add_comand_to_tab(msh->env.sort_tab, cmd);
		if (!dup)
			return ;
		free(msh->env.sort_tab);
		msh->env.sort_tab = tab_dup(dup);
	}
}

void	replace_export(t_msh *msh, char *cmd, int index)
{
	int	pos;
	
	(void)index;
	pos = get_position(msh->env.tab, cmd);
	free(msh->env.tab[pos]);
	msh->env.tab[pos] = ft_strdup(cmd);
}

void	replace_secret_export(t_msh *msh, char *cmd, int index)
{
	int	pos;
	
	(void)index;
	pos = get_position(msh->env.sort_tab, cmd);
	free(msh->env.sort_tab[pos]);
	msh->env.sort_tab[pos] = ft_strdup(cmd);
}

char	**add_comand_to_tab(char **tab, char *cmd)
{
	char	**dup;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (tab[count])
		count++;
	dup = (char **)malloc((count + 2) * sizeof(char *));
	while (i < count)
	{
		dup[i] = tab[i];
		i++;
	}
	dup[i] = ft_strdup(cmd);
	dup[i + 1] = NULL;
	return (dup);
}
