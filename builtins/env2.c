/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:42:57 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/16 15:23:54 by mfinette         ###   ########.fr       */
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
//NEED TO SECURE ENV -I
t_env	init_env(char **envp)
{
	t_env	env;
	char	*dup;
	char	*level;
	int		shlvl;
	int		position;
	
	shlvl = 0;
	if (ft_expand_tab(envp, "SHLVL"))
		shlvl = atoi(ft_expand_tab(envp, "SHLVL"));
	else
		shlvl = 0;
	level = ft_itoa(shlvl + 1);
	dup = ft_strjoin("SHLVL=", level);
	env.tab = envp_dup(envp);
	position = get_position(env.tab, "SHLVL");
	if (position == -1)
		position = tab_len(env.tab);
	free(env.tab[position]);
	free(level);
	env.tab[position] = ft_strdup(dup);
	free(dup);
	env.sort_tab = init_secret_env(envp);
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
	dup = ft_strjoin("SHLVL=", level);
	tab = envp_dup(envp);
	position = get_position(tab, "SHLVL");
	if (position == -1)
		position = tab_len(tab);
	free(tab[position]);
	free(level);
	tab[position] = ft_strdup(dup);
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
