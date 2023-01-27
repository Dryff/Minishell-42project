/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:57:07 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/27 08:44:37 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

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

char	*get_export_cmd(char *line)
{
	return (ft_strnstr(line, "export", 100) + 7);
}

t_env	init_env(char **envp)
{
	int		i;
	t_env	env;

	i = 0;
	env.tab = (char **)ft_calloc(ft_tablen(envp) + 1, sizeof(char *));
	while (i < ft_tablen(envp) && envp[i])
	{
		env.tab[i] = ft_strdup(envp[i]);
		i++;
	}
	env.size = ft_tablen(envp) - 1;
	return (env);
}

void	ft_print_env(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < msh->env.size + 1)
	{
		printf("\e[1;34m%s\e[0m\n", msh->env.tab[i]);
		i++;
	}
}
