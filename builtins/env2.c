/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:42:57 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/20 11:50:35 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

t_env	init_env_i(void)
{
	t_env	env;
	char	*dup;

	env.error = 0;
	env.tab = malloc(sizeof(char *) * 4);
	if (!env.tab)
		return (env.error = 1, env);
	dup = getcwd(NULL, 0);
	if (!dup)
		return (env.error = 1, env);
	env.tab[0] = ft_strdup("SHLVL=0");
	if (!env.tab[0])
		return (env.error = 1, env);
	env.tab[1] = ft_strjoin("PWD=", dup);
	if (!env.tab[1])
		return (env.error = 1, env);
	env.tab[2] = ft_strdup("_=/usr/bin/env");
	if (!env.tab[2])
		return (env.error = 1, env);
	env.tab[3] = NULL;
	env.sort_tab = init_secret_env(env.tab);
	if (!env.sort_tab)
		return (env.error = 1, env);
	free(dup);
	return (env);
}

t_env	init_env(char **envp)
{
	t_env	env;

	env.error = 0;
	if (tab_len(envp) == 0)
		return (init_env_i());
	env.tab = envp_dup(envp);
	if (!env.tab)
		return (env.error = 1, env);
	env.sort_tab = init_secret_env(env.tab);
	if (!env.sort_tab)
		return (env.error = 1, env);
	return (env);
}

void	check_shlvl(t_msh *msh)
{
	int		shlvl;
	char	*dup;
	char	*joined;

	if (!ft_expand_tab(msh->env.tab, "SHLVL"))
		complete_export(msh, "SHLVL=1");
	else
	{
		shlvl = atoi(ft_expand_tab(msh->env.tab, "SHLVL"));
		if (shlvl < 0)
			complete_export(msh, "SHLVL=0");
		if (shlvl >= 999)
			reset_shlvl(msh, shlvl);
		if (shlvl >= 0 && shlvl < 999)
		{
			shlvl++;
			dup = ft_itoa(shlvl);
			joined = ft_strjoin("SHLVL=", dup);
			if (!joined || !dup)
				error_manager(msh, 1);
			complete_export(msh, joined);
			free(dup);
			free(joined);
		}
	}
}

char	**init_secret_env(char **envp)
{
	char	**tab;

	tab = envp_dup(envp);
	if (!tab)
		return (NULL);
	return (tab);
}

void	ft_print_env(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->env.tab[i])
	{
		printf("%s\n", msh->env.tab[i]);
		i++;
	}
}
