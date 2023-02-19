/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:45:07 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/19 14:45:44 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	add_export(t_env *env, char *cmd)
{
	char	**dup;

	dup = add_comand_to_tab(env->tab, cmd);
	env->tab = tab_dup(dup);
	free(dup);
	if (get_position(env->sort_tab, cmd) < 0)
		add_invisible_export(env, cmd);
	sort_tab(env);
}

void	replace_export(t_env *env, char *cmd)
{
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
