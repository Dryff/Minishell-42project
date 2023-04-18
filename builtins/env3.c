/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:50:58 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/18 10:17:15 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	free_env(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->env.tab[i])
	{
		free(msh->env.tab[i]);
		i++;
	}
	free(msh->env.tab);
	i = 0;
	while (msh->env.sort_tab[i])
	{
		free(msh->env.sort_tab[i]);
		i++;
	}
	free(msh->env.sort_tab);
}

char	**envp_dup(char **tab)
{
	int		i;
	int		count;
	char	**dup;

	i = -1;
	count = 0;
	while (tab[count])
		count++;
	dup = (char **)malloc((count + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	while (++i < count)
	{
		dup[i] = ft_strdup(tab[i]);
		if (!dup[i])
			return (NULL);
	}
	dup[i] = NULL;
	return (dup);
}

void	check_env(t_msh *msh)
{
	check_pwd(msh);
	check_shlvl(msh);
	complete_export(msh, "_=/usr/bin/env");
}

void	check_pwd(t_msh *msh)
{
	if (!ft_expand_tab(msh->env.sort_tab, "OLDPWD"))
		add_invisible_export(msh, "OLDPWD");
}

void	reset_shlvl(t_msh *msh, int nb)
{
	ft_err_printf("msh: warning: shell level (%d) too high, resetting to 1\n", nb);
	complete_export(msh, "SHLVL=1");
}
