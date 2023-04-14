/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:57:07 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/14 20:53:20 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	**tab_dup(char **tab)
{
	int		i;
	int		count;
	char	**dup;

	i = -1;
	count = 0;
	while (tab[count])
		count++;
	dup = (char **)malloc((count + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	while (++i < count)
		dup[i] = tab[i];
	dup[i] = NULL;
	free(tab);
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

void	ft_strswap(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == 0 && s2[i] == 0)
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_export_print(char *str)
{
	int	i;
	int	j;

	j = 0;
	if (str[0] == '_' && str[1] == '=')
		return ;
	i = ft_strlen_until(str, '=');
	write(1, "declare -x ", 11);
	if (i == (int)ft_strlen(str))
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		return ;
	}
	while (j <= i)
	{
		write(1, &str[j], 1);
		j++;
	}
	i++;
	write(1, "\"", 1);
	write(1, &str[i], ft_strlen(&str[i]));
	write(1, "\"", 1);
	write(1, "\n", 1);
}
