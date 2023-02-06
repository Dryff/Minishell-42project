/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:51:27 by cgelin            #+#    #+#             */
/*   Updated: 2022/11/16 08:38:42 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_len(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr_int(int n)
{	
	int			nb;

	nb = n;
	if (n == -2147483648)
		return (ft_putstr_int("-2147483648"));
	if (n < 0)
	{	
		n *= -1;
		ft_putchar_int('-');
	}
	if (n > 9)
		ft_putnbr_int(n / 10);
	ft_putchar_int((n % 10) + 48);
	return (ft_putnbr_len(nb));
}
