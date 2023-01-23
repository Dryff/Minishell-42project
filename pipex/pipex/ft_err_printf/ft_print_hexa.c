/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:02:15 by cgelin            #+#    #+#             */
/*   Updated: 2022/11/16 08:09:24 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_hexa_len(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

unsigned int	print_hexa(long n, char caps)
{	
	char		*min;
	char		*maj;
	int			nb;

	nb = n;
	min = "0123456789abcdef";
	maj = "0123456789ABCDEF";
	if (n == 16)
	{
		ft_putstr_int("10");
		return (ft_hexa_len(nb));
	}
	if (n > 16)
		print_hexa(n / 16, caps);
	if (caps == 'X')
		ft_putchar_int(maj[n % 16]);
	else
		ft_putchar_int(min[n % 16]);
	return (ft_hexa_len(nb));
}

unsigned long long	ft_hexa_len_adress(unsigned long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

int	print_hexa_adress(unsigned long long n, char caps)
{	
	char				*min;
	char				*maj;
	unsigned long long	nb;

	nb = n;
	min = "0123456789abcdef";
	maj = "0123456789ABCDEF";
	if (n == 16)
		ft_putchar_int('1');
	if (n > 16)
		print_hexa_adress(n / 16, caps);
	if (caps == 'X')
		ft_putchar_int(maj[n % 16]);
	else
		ft_putchar_int(min[n % 16]);
	return (ft_hexa_len_adress(nb) + 2);
}
