/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:42:57 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/27 15:56:35 by mfinette         ###   ########.fr       */
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
	char	*level;

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
	char	*dup;
	char	*level;
	int		shlvl;
	int		position;
	
	shlvl = 0;
	env.error = 0;
	if (tab_len(envp) == 0)
		return (init_env_i());
	if (ft_expand_tab(envp, "SHLVL"))
		shlvl = atoi(ft_expand_tab(envp, "SHLVL"));
	else
		shlvl = 0;
	level = ft_itoa(shlvl + 1);
	if (!level)
		return (env.error = 1, env);
	dup = ft_strjoin("SHLVL=", level);
	if (!dup)
		return (env.error = 1, env);
	env.tab = envp_dup(envp);
	if (!env.tab)
		return (env.error = 1, env);
	position = get_position(env.tab, "SHLVL");
	if (position == -1)
		position = tab_len(env.tab);
	free(env.tab[position]);
	free(level);
	env.tab[position] = ft_strdup(dup);
	if (!env.tab[position])
		return (env.error = 1, env);
	free(dup);
	env.sort_tab = init_secret_env(envp);
	if (!env.sort_tab)
		return (env.error = 1, env);
	return (env);
}

char **init_secret_env(char **envp)
{
	char	**tab;
	char	*level;
	char	*dup;
	int		shlvl;
	int		position;

	shlvl = 0;
	if (ft_expand_tab(envp, "SHLVL"))
		shlvl = atoi(ft_expand_tab(envp, "SHLVL"));
	else
		shlvl = 0;
	level = ft_itoa(shlvl + 1);
	if (!level)
		return (NULL);
	dup = ft_strjoin("SHLVL=", level);
	if (!dup)
		return (NULL);
	tab = envp_dup(envp);
	if (!tab)
		return (NULL);
	position = get_position(tab, "SHLVL");
	if (position == -1)
		position = tab_len(tab);
	free(tab[position]);
	free(level);
	tab[position] = ft_strdup(dup);
	if (!tab[position])
		return (NULL);
	free(dup);
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
