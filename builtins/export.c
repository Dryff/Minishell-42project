/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:36:02 by mfinette          #+#    #+#             */
/*   Updated: 2023/01/27 08:43:58 by mfinette         ###   ########.fr       */
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

static	int	is_in_charset(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
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

int	ft_export(t_env *env, char *cmd)
{
	if (valid_export(cmd) == WRONG_EXPORT)
		return (printf("msh: export: '%s': not a valid identifier\n", cmd), 0);
	if (valid_export(cmd) == EMPTY_EXPORT)
		return (0);
	if (valid_export(cmd) == VALID_EXPORT)
	{
		if (get_position(env, cmd) < 0)
		{
			env->size++;
			env->tab[env->size] = ft_strdup(cmd);
		}
		else
		{
			free(env->tab[get_position(env, cmd)]);
			env->tab[get_position(env, cmd)] = ft_strdup(cmd);
		}
	}
	return (0);
}
