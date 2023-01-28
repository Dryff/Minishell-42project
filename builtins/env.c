/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:57:07 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/28 12:31:27 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

static int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size - 1)
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

t_env	init_env(char **envp)
{
	int		i;
	t_env	env;

	i = 0;
	env.tab = tab_dup(envp);
	env.size = ft_tablen(envp) - 1;
	env.sort_tab = tab_dup(env.tab);
	env.sort_size = env.size;
	printf("tablen = %d\n", ft_tablen(envp) + 1);
	return (env);
}

void	ft_print_env(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < msh->env.size + 1)
	{
		printf("\e[0;34m%s\e[0m\n", msh->env.tab[i]);
		i++;
	}
}

char	**tab_dup(char **tab)
{
	int		i;
	int		count;
	char	**dup;
	
	i = 0;
	count = 0;
	while (tab[count])
		count++;
	dup = (char **)malloc((count + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	while (i < count)
	{
		dup[i] = ft_strdup(tab[i]);
		if (!dup[i])
			return (NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	free_tab(char **tab)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (tab[size])
		size++;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_declare_print(t_env *env)
{
	int	i;
	char **dup;
	
	i = 0;
	dup = tab_dup(env->sort_tab);
	free_tab(env->sort_tab);
	//env->sort_tab = sort_env(env->sort_tab);
	free_tab(dup);
	while (env->sort_tab[i])
	{
		printf("\e[2;93mdeclare -x \"%s\"\e[0m\n", env->sort_tab[i]);
		i++;
	}
}
