/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:01:38 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/25 17:25:04 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*get_expand_cmd(char *str)
{
	return (str + 4);
}

char	*ft_expand(t_env *env, char *cmd)
{
	int		i;
	int		pos;
	char	*expanded;

	i = 0;
	expanded = NULL;
	while (env->tab[i])
	{
		if (ft_strstr(env->tab[i], cmd))
		{
			if (env->tab[i][0] == cmd[0] && env->tab[i][ft_strlen(cmd)] == '=')
			{
				pos = ft_strlen_until(env->tab[i], '=') + 1;
				expanded = env->tab[i] + pos;
				return (expanded);
			}
		}
		i++;
	}
	return (NULL);
}

char	*ft_expand_tab(char **tab, char *cmd)
{
	int		i;
	int		pos;
	char	*expanded;

	i = 0;
	expanded = NULL;
	while (tab[i])
	{
		if (ft_strstr(tab[i], cmd))
		{
			if (tab[i][0] == cmd[0] && tab[i][ft_strlen(cmd)] == '=')
			{
				pos = ft_strlen_until(tab[i], '=') + 1;
				expanded = tab[i] + pos;
				return (expanded);
			}
		}
		i++;
	}
	return (NULL);
}