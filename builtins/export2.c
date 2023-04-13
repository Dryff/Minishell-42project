/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:45:07 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/13 11:09:07 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	add_export(t_msh *msh, char *cmd)
{
	char	**dup;

	dup = add_comand_to_tab(msh->env.tab, cmd);
	if (!dup)
		return ((void)(msh->error = 1));
	free(msh->env.tab);
	msh->env.tab = tab_dup(dup);
	if (!msh->env.tab)
		return ((void)(msh->error = 1));
	sort_tab(&msh->env);
}

void	add_invisible_export(t_msh *msh, char *cmd)
{
	int		pos;
	char	**dup;

	pos = get_position(msh->env.sort_tab, cmd);
	if (pos == -2)
		return ((void)(msh->error = 1));
	if (pos < 0)
	{
		dup = add_comand_to_tab(msh->env.sort_tab, cmd);
		if (!dup)
			return ((void)(msh->error = 1));
		free(msh->env.sort_tab);
		msh->env.sort_tab = tab_dup(dup);
		if (!msh->env.sort_tab)
			return ((void)(msh->error = 1));
	}
}

void	replace_export(t_msh *msh, char *cmd, int index)
{
	int	pos;

	(void)index;
	pos = get_position(msh->env.tab, cmd);
	if (pos == -2)
		return ((void)(msh->error = 1));
	free(msh->env.tab[pos]);
	msh->env.tab[pos] = ft_strdup(cmd);
	if (!msh->env.tab[pos])
		return ((void)(msh->error = 1));
}

void	replace_secret_export(t_msh *msh, char *cmd, int index)
{
	int	pos;

	(void)index;
	pos = get_position(msh->env.sort_tab, cmd);
	if (pos == -2)
		return ((void)(msh->error = 1));
	free(msh->env.sort_tab[pos]);
	msh->env.sort_tab[pos] = ft_strdup(cmd);
	if (!msh->env.sort_tab[pos])
		return ((void)(msh->error = 1));
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
	if (!dup)
		return (NULL);
	while (i < count)
	{
		dup[i] = tab[i];
		i++;
	}
	dup[i] = ft_strdup(cmd);
	if (!dup[i])
		return (NULL);
	dup[i + 1] = NULL;
	return (dup);
}
