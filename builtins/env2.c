/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:42:57 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/19 14:43:22 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->tab[i])
	{
		free(env->tab[i]);
		i++;
	}
	free(env->tab);
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
		dup[i] = tab[i];
	dup[i] = NULL;
	return (dup);
}

t_env	init_env(char **envp)
{
	t_env	env;

	env.tab = envp_dup(envp);
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
