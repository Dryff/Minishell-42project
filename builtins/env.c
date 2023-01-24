/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:57:07 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/24 11:30:19 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

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
	while (i < env->size - 1)
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

char	*get_export_cmd(char *line)
{
	 return (ft_strnstr(line, "export", 100) + 7);
}

t_env	init_env(char **envp)
{
	int		i;
	t_env	env;

	i = 0;
	env.tab = malloc((ft_tablen(envp) + 1) * sizeof(char *));
	// if (!env.tab)
	// 	return (NULL);
	while (i < ft_tablen(envp) && envp[i])
	{
		env.tab[i] = ft_strdup(envp[i]);
		i++;
	}
	env.size = ft_tablen(envp) + 1;
	return (env);
}

void	ft_export(t_msh *msh, char *cmd)
{
	int	i;
	char	**tab_dup;

	i = 0;
	msh->env.size++;
	tab_dup = ft_tabdup(msh->env.tab);
	free_env(&msh->env);
	msh->env.tab = malloc(msh->env.size * sizeof(char *));
	while (msh->env.tab[i])
	{
		msh->env.tab[i] = ft_strdup(tab_dup[i]);
		i++;
	}
	msh->env.tab[msh->env.size] = ft_strdup(cmd);
}

void	ft_print_env(t_msh msh)
{
	int	i;

	i = 0;
	while (i < msh.env.size - 1)
	{
		printf("\e[1;34m%s\e[0m\n", msh.env.tab[i]);
		i++;
	}
}

// void	unset_var(t_env *env, char *cmd)
// {
// 	int	i;
// 	int	pos;

// 	i = 0;
// 	pos = -1;
// 	while (env->tab[i] && pos == 0)
// 	{
// 		if (ft_strstr(env->tab[i], cmd))
// 			pos = i;
// 		i++;
// 	}
// 	if (pos != -1)
// 	{
// 		i = pos;
// 		while (i < env->size)
// 		{
// 			env->tab[i] = env->tab[i + 1];
// 			i++;
// 		}
// 		env->tab[i] = 0;
// 	}
// }
