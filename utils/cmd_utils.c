/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:34 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/27 19:04:02 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	if (!len)
		return (NULL);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			if (needle[j + 1] == '\0')
			{
				if (j + i > len - 1)
					return (0);
				return ((char *)&haystack[i]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int ft_strstr(const char *str, const char *to_find)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if ((!str || !to_find))
		return (0);
	if (to_find[0] == 0)
		return (0);
	while (str[i])
	{
		while (to_find[j])
		{
			if (str[i + j] != to_find[j])
				break;
			j++;
			if (!to_find[j])
				return (1);
		}
		j = 0;
		i++;
	}
	return (0);
}

int search_cmd(const char *hs, const char *nee)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (hs[i])
	{
		j = 0;
		while (nee[j] == hs[i + j])
		{
			if (nee[j + 1] == '\0' && (hs[i + j + 1] == ' ' || hs[i + j + 1] == '=' || hs[i + j + 1] == '\0'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int ft_strlen_until(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int is_in_charset(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

void sort_tab(t_env *env)
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