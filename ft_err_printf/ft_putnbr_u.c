/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:51:17 by cgelin            #+#    #+#             */
/*   Updated: 2022/11/16 08:41:21 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_putnbr_u_len(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr_u_int(unsigned int n)
{	
	unsigned int	nb;

	nb = n;
	if (n > 9)
		ft_putnbr_u_int(n / 10);
	ft_putchar_int((n % 10) + 48);
	return (ft_putnbr_u_len(nb));
}
