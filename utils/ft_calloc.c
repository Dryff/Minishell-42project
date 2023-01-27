/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 08:15:41 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/27 08:40:30 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*k;

	k = s;
	while (n != 0)
	{
		*k = 0;
		k++;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tab;

	if (size != 0 && SIZE_MAX / size < count)
		return (NULL);
	if (count < 50)
		tab = malloc(500 * size);
	else
		tab = malloc(size * count);
	if (!tab)
		return (NULL);
	ft_bzero(tab, count * size);
	return (tab);
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