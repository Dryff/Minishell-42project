/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:36:02 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/16 13:38:55 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

#define VALID_EXPORT 1
#define WRONG_EXPORT 2
#define EMPTY_EXPORT 3
#define EXISTING_EXPORT 4

int	get_position(char **tab, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_substr(cmd, 0, ft_strlen_until(cmd, '='));
	if (!temp)
		return (0);
	while (tab[i])
	{
		if (ft_strstr(tab[i], temp))
		{
			if (tab[i][ft_strlen(temp)] == '=' || !tab[i][ft_strlen(temp)])
			{
				free(temp);
				return (i);
			}
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

void	ft_declare_print(t_env *env)
{
	int	i;
	int	j;
	int	size;

	i = -1;
	size = 0;
	while (env->sort_tab[size])
		size++;
	while (env->sort_tab[++i])
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(env->sort_tab[i], env->sort_tab[j]) > 0)
				ft_strswap(&env->sort_tab[i], &env->sort_tab[j]);
			j++;
		}
	}
	i = -1;
	while (env->sort_tab[++i])
		ft_export_print(env->sort_tab[i]);
}

// void	ft_declare_print(t_env *env)
// {
// 	int	i;
	
// 	i = 0;
// 	while (env->sort_tab[i])
// 	{
// 		printf("(EXPORT) %s\n", env->sort_tab[i]);
// 		i++;
// 	}
// }

int	complete_export(t_msh *msh, char *cmd)
{
	int		pos;
	char	*purecmd;

	purecmd = ft_substr(cmd, 0, ft_strlen_until(cmd, '='));
	if (!purecmd)
		return (0);
	pos = get_position(msh->env.tab, purecmd);
	if (get_position(msh->env.tab, purecmd) < 0)
		add_export(msh, cmd);
	else
		replace_export(msh, cmd, pos);
	if (get_position(msh->env.sort_tab, purecmd) < 0)
		add_invisible_export(msh, cmd);
	else
		replace_secret_export(msh, cmd, pos);
	free(purecmd);
	return (1);
}

int	ft_export(t_msh *msh, int cmd_id)
{
	char	*cmd;
	int		i;

	i = 0;
	while (msh->cmd[cmd_id].param[i])
		i++;
	if (i < 2)
		ft_declare_print(&msh->env);
	i = 1;
	while (msh->cmd[cmd_id].param[i])
	{
		cmd = msh->cmd[cmd_id].param[i];
		if (valid_export(cmd) == WRONG_EXPORT)
			printf("msh: export: '%s': not a valid identifier\n", cmd);
		else if (valid_export(cmd) == EMPTY_EXPORT)
			add_invisible_export(msh, cmd);
		else if (valid_export(cmd) == VALID_EXPORT)
		{
			if (!complete_export(msh, cmd))
				return (1);
		}
		i++;
	}
	return (0);
}
