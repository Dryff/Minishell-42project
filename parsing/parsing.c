/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/24 12:09:41 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_cmd_nbr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{	
		if (is_delimiter(str, i))
			count++;
		i++;
	}
	return (count);
}

int	parse_line(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	msh->cmd_nbr = get_cmd_nbr(msh->line);
	msh->cmd = malloc(sizeof(t_cmd) * msh->cmd_nbr);
	while (msh->line[i])
	{
		while (msh->line[i] && (is_delimiter(msh->line, i) \
		|| is_white_space(msh->line[i])))
			i++;
		if (msh->line[i])
			msh->cmd[j++].param = ft_split_until(*msh, ' ');
		while (msh->line[i] && !is_delimiter(msh->line, i))
			i++;
	}
	j = 0;
	printf("cmd_nbr : %d\n-----\n", msh->cmd_nbr);
	// while (j < msh->cmd_nbr)
	// 	printf("%s\n", msh->cmd[j++].param[0]);
	return (1);
}
