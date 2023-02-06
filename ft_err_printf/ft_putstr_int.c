/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:58:16 by cgelin            #+#    #+#             */
/*   Updated: 2022/12/08 16:22:17 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_int(int c)
{
	write(2, &c, 1);
	return (1);
}

int	ft_putstr_int(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(2, "(null)", 6);
		i += 6;
		return (i);
	}
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	return (i);
}
