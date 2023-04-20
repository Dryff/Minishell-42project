/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:10:01 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/20 13:12:26 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_position(char **tab, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_substr(cmd, 0, ft_strlen_until(cmd, '='));
	if (!temp)
		return (-2);
	while (tab[i])
	{
		if (ft_strstr(tab[i], temp))
		{
			if (tab[i][ft_strlen(temp)] == '=' || !tab[i][ft_strlen(temp)])
			{
				if (tab[i][0] == temp[0])
				{
					free(temp);
					return (i);
				}
			}
		}
		i++;
	}
	free(temp);
	return (-1);
}

int	is_valid_c(char c)
{
	if (is_in_charset(c, "#%?!@/-+={}.,:"))
		return (0);
	if (!is_in_charset(c, "0123456789"))
	{
		if (!is_in_charset(c, "abcdefghijklmnopqrstuvwxyz"))
		{
			if (!is_in_charset(c, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"))
				return (0);
		}
	}
	return (1);
}
