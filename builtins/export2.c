/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:45:07 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/04 14:26:03 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	add_export(t_msh *msh, char *cmd)
{
	char	**dup;

	dup = add_comand_to_tab(msh->env.tab, cmd);
	if (!dup)
		return ;
	msh->env.tab = tab_dup(dup);
	free(dup);
	add_invisible_export(&msh->env, cmd);
	sort_tab(&msh->env);
}

void	add_invisible_export(t_env *env, char *cmd)
{
	char	**dup;

	if (get_position(env->sort_tab, cmd) < 0)
	{
		dup = add_comand_to_tab(env->sort_tab, cmd);
		if (!dup)
			return ;
		env->sort_tab = tab_dup(dup);
		free(dup);
	}
}

void	replace_export(t_env *env, char *cmd, int index)
{
	int	pos;
	
	(void)index;
	pos = get_position(env->tab, cmd);
	free(env->tab[pos]);
	env->tab[pos] = ft_strdup(cmd);
	env->sort_tab[pos] = ft_strdup(cmd);
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
