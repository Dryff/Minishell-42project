/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:49:50 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/25 17:50:02 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	else
		return (nbr);
}

static void	ft_strrev(char *str)
{
	size_t	length;
	size_t	i;
	char	tmp;

	length = ft_strlen(str);
	i = 0;
	while (i < length / 2)
	{
		tmp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tmp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		is_neg;
	size_t	len;

	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	str = ft_calloc(11 + is_neg, sizeof(*str));
	if (!str)
		return (0);
	if (n == 0)
		str[0] = '0';
	len = 0;
	while (n != 0)
	{
		str[len] = '0' + ft_abs(n % 10);
		n = (n / 10);
		len++;
	}
	if (is_neg)
		str[len] = '-';
	ft_strrev(str);
	return (str);
}