/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laquarium <laquarium@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:42:57 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/30 16:29:25 by laquarium        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	free_env(t_msh msh)
{
	int	i;

	i = 0;
	while (msh.env.tab[i])
	{
		free(msh.env.tab[i]);
		i++;
	}
	free(msh.env.tab);
	i = 0;
	while (msh.env.sort_tab[i])
	{
		free(msh.env.sort_tab[i]);
		i++;
	}
	free(msh.env.sort_tab);	
}

char	*get_export_cmd(char *line)
{
	return (ft_strnstr(line, "export", 100) + 7);
}

static int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
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

t_env init_env_i(void)
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
	env.tab[0] = ft_strdup("SHLVL=1");
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

void	check_env(t_msh *msh)
{
	check_pwd(msh);
	check_shlvl(msh);
}

void	check_pwd(t_msh *msh)
{
	if (!ft_expand_tab(msh->env.sort_tab, "OLDPWD"))
		add_invisible_export(msh, "OLDPWD");
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
		{
			printf("resetting SHLVL to 1, limit exceeded(1000)\n");
			complete_export(msh, "SHLVL=1");
		}
		if (shlvl >=0 && shlvl < 999)
		{
			shlvl++;
			dup = ft_itoa(shlvl);
			joined = ft_strjoin("SHLVL=", dup);
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
