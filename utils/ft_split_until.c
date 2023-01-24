/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_until.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:16:26 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/24 11:30:17 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

static int	check_charset(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static int	count_str(char const *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && check_charset(str[i], charset))
			i++;
		if (str[i])
			count++;
		while (str[i] && !check_charset(str[i], charset))
			i++;
	}
	return (count);
}

static char	*ft_word(char const *str, int i, char charset)
{
	char	*dest;
	int		j;
	int		len;
	int		k;

	k = i;
	len = 0;
	while (str[i] && !check_charset(str[i], charset))
	{
		i++;
		len++;
	}
	j = 0;
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	while (j < len)
		dest[j++] = str[k++];
	dest[j] = '\0';
	return (dest);
}

static char	**ft_freeall(char **strings, int ind, char c, char *s)
{
	size_t	i;

	i = 0;
	if (ind == 1)
	{
		if (!strings)
		{
			while (strings[i] != NULL)
				free(strings[i++]);
			free (strings);
			return (NULL);
		}
	}
	else
	{
		if (!s)
			return (NULL);
		strings = malloc(sizeof(char *) * count_str(s, c) + 1);
		if (!strings)
			return (NULL);
	}
	return (strings);
}

char	**ft_split_until(char const *s, char c, int k)
{
	int		j;
	int		i;
	char	**strings;

	j = 0;
	i = 0;
	strings = NULL;
	strings = ft_freeall(strings, 0, c, (char *)s);
	if (!strings)
		return (NULL);
	while (s[i] && i < k)
	{
		while (s[i] && check_charset(s[i], c))
			i++;
		if (s[i])
		{
			strings[j++] = ft_word(s, i, c);
			if (!ft_freeall(strings, 1, c, (char *)s))
				return (NULL);
		}
		while (s[i] && !check_charset(s[i], c) && i < k)
			i++;
	}
	strings[j] = 0;
	return (strings);
}

