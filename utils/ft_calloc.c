/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 08:15:41 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/15 17:50:57 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"
#include <stdint.h>

void	update_msh_status(int status)
{
	g_status = status;
}

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
	tab = malloc(size * count);
	if (!tab)
		return (NULL);
	ft_bzero(tab, count * size);
	return (tab);
}
