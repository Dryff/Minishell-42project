/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:57:07 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/23 11:44:00 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*ft_strdup(const char *src)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!cpy)
		return (0);
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

static	int	ft_tablen(char **tab)
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
	while (env->tab[i])
	{
		free(env->tab[i]);
		i++;
	}
	free(env->tab);
}

static	char	**ft_tabdup(char **tab)
{
	int	i;
	char	**dup;
	
	i = 0;
	dup = (char **)malloc((ft_tablen(tab) + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	while (tab[i])
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	return (dup);
}

t_env	init_env(char **envp)
{
	int		i;
	t_env	env;

	i = 0;
	env.tab = malloc((ft_tablen(envp) + 1) * sizeof(char *));
	while (i < ft_tablen(envp) && envp[i])
	{
		env.tab[i] = ft_strdup(envp[i]);
		i++;
	}
	env.size = ft_tablen(envp) + 1;
	i = 0;
	while (i < ft_tablen(envp))
	{
	//	printf("%s\n", env.tab[i]);
		i++;
	}
	return (env);
}

void	export_var(t_env *env, char *cmd)
{
	int	i;
	char	**tab_dup;

	i = 0;
	env->size++;
	tab_dup = ft_tabdup(env->tab);
	free_env(env);
	env->tab = malloc(env->size * sizeof(char *));
	while (env->tab[i])
	{
		env->tab[i] = ft_strdup(tab_dup[i]);
		i++;
	}
	env->tab[env->size] = ft_strdup(cmd);
	//PRINT
	while (*env->tab)
	{
		printf("%s\n", *env->tab);
		env->tab++;
	}	
}


void	unset_var(t_env *env, char *cmd)
{
	int	i;
	int	pos;

	i = 0;
	pos = -1;
	while (env->tab[i] && pos = 0)
	{
		if (ft_strstr(env->tab[i], cmd))
			pos = i;
		i++;
	}
	if (pos != -1)
	{
		i = pos;
		while (i < env->size)
		{
			env->tab[i] = env->tab[i + 1];
			i++;
		}
		env->tab[i] = 0;
	}
}
