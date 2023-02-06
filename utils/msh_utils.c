/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:25:58 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/02 14:21:56 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	n--;
	while (i < n && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin_by_sep(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = ft_strlen((char *)s1) + 1;
	len2 = ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '|';
	i = 0;
	while (s2 && s2[i])
		str[len1++] = s2[i++];
	str[len1] = '|';
	str[++len1] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
