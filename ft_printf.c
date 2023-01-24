/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:47:31 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/24 11:30:18 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

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

int	get_next_char_count(char *str, int i, va_list args)
{
	if (str[i] == 'c')
		return (ft_putchar_int(va_arg(args, int)));
	else if (str[i] == 's')
		return (ft_putstr_int(va_arg(args, char *)));
	else if (str[i] == 'd' || str[i] == 'i')
		return (ft_putnbr_int(va_arg(args, int)));
	return (0);
}

int	ft_err_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, str);
	if (write(2, 0, 0) != 0)
		return (va_end(args), -1);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
			len += get_next_char_count((char *)str, ++i, args);
		else
		{
			write(2, &str[i], 1);
			len++;
		}
		i++;
	}
	return (va_end(args), len);
}
