/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:20:09 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/13 10:55:47 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	ft_strlen_until(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	is_in_charset(char c, char *str)
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

void	sort_tab(t_env *env)
{
	int		i;
	int		j;
	int		count;
	char	*temp;

	count = 0;
	while (env->sort_tab[count])
		count++;
	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (strcmp(env->sort_tab[i], env->sort_tab[j]) > 0)
			{
				temp = env->sort_tab[i];
				env->sort_tab[i] = env->sort_tab[j];
				env->sort_tab[j] = temp;
			}
			j++;
		}
		i++;
	}
}

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

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
