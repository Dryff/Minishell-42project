/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:45:07 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/27 14:31:27 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	add_export(t_msh *msh, char *cmd)
{
	char	**dup;

	dup = add_comand_to_tab(msh->env.tab, cmd);
	msh->env.tab = tab_dup(dup);
	free(dup);
	add_invisible_export(&msh->env, cmd);
	sort_tab(&msh->env);
}

void	replace_export(t_env *env, char *cmd, int index)
{
	(void)index;
	env->tab[get_position(env->tab, cmd)] = ft_strdup(cmd);
	env->sort_tab[get_position(env->sort_tab, cmd)] = ft_strdup(cmd);
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
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	dup[i] = ft_strdup(cmd);
	dup[i + 1] = NULL;
	return (dup);
}

void	add_invisible_export(t_env *env, char *cmd)
{
	char	**dup;

	if (get_position(env->sort_tab, cmd) < 0)
	{
		dup = add_comand_to_tab(env->sort_tab, cmd);
		env->sort_tab = tab_dup(dup);
		free(dup);
	}
}
