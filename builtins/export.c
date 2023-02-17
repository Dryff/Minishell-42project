/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:36:02 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/17 10:30:03 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

#define VALID_EXPORT 1
#define WRONG_EXPORT 2
#define EMPTY_EXPORT 3
#define EXISTING_EXPORT 4

static	int	get_position(char **tab, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_substr(cmd, 0, ft_strlen_until(cmd, '=') - 1);
	if (!temp)
	    return (0);
	while (tab[i])
	{
		if (ft_strstr(tab[i], temp))
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
	if (is_in_charset(c, "#%?!@/-+={}.,:"))
		return (0);
	return (1);
}

static	int	valid_export(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] >= '0' && cmd[i] <= '9')
		return (WRONG_EXPORT);	
	while (i < ft_strlen_until(cmd, '='))
	{
		if (!is_valid_c(cmd[i]))
			return (WRONG_EXPORT);
		i++;
	}
	if (!is_in_charset('=', cmd))
		return (EMPTY_EXPORT);
	return (VALID_EXPORT);
}

void	add_export(t_env *env, char *cmd)
{
	char **dup;
	
	dup = add_comand_to_tab(env->tab, cmd);
	env->tab = tab_dup(dup);
	free(dup);
	if (get_position(env->sort_tab, cmd) < 0)
		add_invisible_export(env, cmd);
	sort_tab(env);
}

void	replace_export(t_env *env, char *cmd)
{
	//free(env->tab[get_position(env->tab, cmd)]);
	//free(env->tab[get_position(env->sort_tab, cmd)]);
	env->tab[get_position(env->tab, cmd)] = ft_strdup(cmd);
	env->sort_tab[get_position(env->sort_tab, cmd)] = ft_strdup(cmd);
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
		i++;
	}
	dup[i] = ft_strdup(cmd);
	dup[i + 1] = NULL;
	return (dup);
}

void	add_invisible_export(t_env *env, char *cmd)
{
	char **dup;
	
	if (get_position(env->sort_tab, cmd) < 0)
	{
		dup = add_comand_to_tab(env->sort_tab, cmd);
		env->sort_tab = tab_dup(dup);
		free(dup);
	}
}

int	ft_export(t_msh *msh, int cmd_id)
{
	char *cmd;
	int i;

	i = 0;
	while (msh->cmd[cmd_id].param[i])
		i++;
	if (i < 2) // just export
		ft_declare_print(&msh->env);
	i = 1;
	while (msh->cmd[cmd_id].param[i])
	{
		cmd = msh->cmd[cmd_id].param[i];
		printf("%s\n",cmd);
		if (valid_export(cmd) == WRONG_EXPORT) //error export
			printf("msh: export: '%s': not a valid identifier\n", cmd);
		else if (valid_export(cmd) == EMPTY_EXPORT) // export without '='
			add_invisible_export(&msh->env, cmd);
		else if (valid_export(cmd) == VALID_EXPORT) // real export
		{
			if (get_position(msh->env.tab, cmd) < 0)
				add_export(&msh->env, cmd);
			else
				replace_export(&msh->env, cmd);
		}
		i++;
	}
	return (0);
}