/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:47:42 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/17 17:08:49 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	if (c == 0)
		return ((char *)(&s[i]));
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(&s[i]));
		i--;
	}
	return (0);
}


int is_minishell(char *cmd, char *name)
{
    char    *tmp;

    tmp = ft_strrchr(cmd, '/');
    if (!tmp)
        return (0);
    tmp++;
    name = name + 2;
    if (ft_strcmp(tmp, name) == 0)
        return (1);
    else
        return (0);
}