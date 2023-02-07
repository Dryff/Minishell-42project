/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:57:07 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/28 19:12:41 by cgelin           ###   ########.fr       */
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

t_env	init_env(char **envp)
{
	t_env	env;

	env.tab = tab_dup(envp);
	env.sort_tab = tab_dup(env.tab);
	return (env);
}

void	ft_print_env(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->env.tab[i])
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

static	void	ft_strswap(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

static	int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

void	ft_declare_print(t_env *env)
{
	int	i;
	int	j;
	int	size;
	
	i = 0;
	size = 0;
	while (env->sort_tab[size])
		size++;
	while (env->sort_tab[i])
	{
		j = i + 1;
		while (j < size - 1)
		{
			if (ft_strcmp(env->sort_tab[i], env->sort_tab[j]) > 0)
				ft_strswap(&env->sort_tab[i], &env->sort_tab[j]);
			j++;
		}
		i++;
	}
	//env->sort_tab[i] = 0;
	i = 0;
	while (env->sort_tab[i])
	{
		printf("\e[2;93mdeclare -x \"%s\"\e[0m\n", env->sort_tab[i]);
		i++;
	}
}