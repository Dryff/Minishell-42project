/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:36:02 by mfinette          #+#    #+#             */
/*   Updated: 2023/01/28 12:26:40 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

#define VALID_EXPORT 1
#define WRONG_EXPORT 2
#define EMPTY_EXPORT 3
#define EXISTING_EXPORT 4

static	int	get_position(t_env *env, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_substr(cmd, 0, ft_strlen_until(cmd, '='));
	while (i < env->size + 1)
	{
		if (ft_strstr(env->tab[i], temp))
		{
			free(temp);
			return (i);
		}
		i++;
	}
	free(temp);
	return (-1);
}

static	int	is_valid_c(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	if (is_in_charset(c, "#%?!@/-+={}.,:"))
		return (0);
	return (1);
}

static	int	valid_export(char *cmd)
{
	int	i;

	i = 1;
	if (!is_valid_c(cmd[0]))
		return (WRONG_EXPORT);
	if (!is_in_charset('=', cmd))
		return (EMPTY_EXPORT);
	return (VALID_EXPORT);
}

void	add_export(t_env *env, char *cmd)
{
	env->size++;
	env->tab[env->size] = ft_strdup(cmd); //modifier ici sinon c la deshhhhhhhh
	env->sort_size++;
	env->sort_tab[env->size] = ft_strdup(cmd);
	sort_tab(env);	
}

void	replace_export(t_env *env, char *cmd)
{
	free(env->tab[get_position(env, cmd)]);	
	env->tab[get_position(env, cmd)] = ft_strdup(cmd);	
}

char	**add_comand_to_tab(char **tab, char *cmd)
{
	char	**dup;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (tab[count])
		count++;
	dup = (char **)malloc((count + 2) * sizeof(char *));
	while (i < count)
	{
		dup[i] = ft_strdup(tab[i]);
		printf("(BEFORE)dup[%d] = %s\n", i, dup[i]);
		i++;
	}
	dup[i] = ft_strdup(cmd);
	printf("(BEFORE)dup[%d] = %s\n", i, dup[i]);
	dup[i + 1] = NULL;
	printf("(BEFORE)dup[%d] = %s\n", i + 1, dup[i + 1]);
	i = 0;
	while (dup[i])
	{
		printf("dup[%d] = %s\n", i, dup[i]);
		i++;
	}
	printf("dup[%d] = %s\n", i, dup[i]);	
	return (dup);
}

void	add_invisible_export(t_env *env, char *cmd)
{
	char **dup;
	
	dup = add_comand_to_tab(env->sort_tab, cmd);
	free_tab(env->sort_tab);
	// int	i = 0;
	// while (env->sort_tab[i])
	// {
	// 	printf("sort_tab[%d] = %s\n", i, env->sort_tab[i]);
	// 	i++;
	// }
	// 	printf("sort_tab[%d] = %s\n", i, env->sort_tab[i]);
	// i = 0;
	// while (dup[i])
	// {
	// 	printf("dup[%d] = %s\n", i, dup[i]);
	// 	i++;
	// }
	// printf("dup[%d] = %s\n", i, dup[i]);
	//env->sort_tab = tab_dup(dup);
	free(dup);
}

int	ft_export(t_env *env, char *cmd)
{
	if (ft_strlen(cmd) < 1) // just export
		ft_declare_print(env);
	else if (valid_export(cmd) == WRONG_EXPORT) //error export
		printf("msh: export: '%s': not a valid identifier\n", cmd);
	else if (valid_export(cmd) == EMPTY_EXPORT) // export without '='
		add_invisible_export(env, cmd);
	else if (valid_export(cmd) == VALID_EXPORT) // real export
	{
		if (get_position(env, cmd) < 0)
			add_export(env, cmd);
		else
			replace_export(env, cmd);
	}
	return (0);
}
