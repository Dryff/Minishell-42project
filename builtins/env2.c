/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:42:57 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/26 18:03:14 by mfinette         ###   ########.fr       */
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
		dup[i] = ft_strdup(tab[i]);
	dup[i] = NULL;
	return (dup);
}

t_env	init_env(char **envp)
{
	t_env	env;
	char	*dup;
	int		shlvl;
	int		position;
	
	shlvl = 0;
	if (ft_expand_tab(envp, "SHLVL"))
		shlvl = atoi(ft_expand_tab(envp, "SHLVL"));
	dup = ft_strjoin("SHLVL=", ft_itoa(shlvl + 1));
	env.tab = envp_dup(envp);
	position = get_position(env.tab, "SHLVL");
	free(env.tab[position]);
	env.tab[position] = ft_strdup(dup);
	env.sort_tab = tab_dup(env.tab);
	return (env);
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
