/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:17:24 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/15 16:18:37 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

static	int	ft_putstr(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}

static	int	is_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static	void	echo_print(t_msh *msh, int cmd_id, int print, int i)
{
	if (print)
	{
		ft_putstr(msh->cmd[cmd_id].param[i]);
		// printf("\nPARAM = %s\n", msh->cmd[cmd_id].param[i]);
		// printf("\nNEXT PARAM = %s\n", msh->cmd[cmd_id].param[i + 1]);
		if (msh->cmd[cmd_id].param[i + 1])
			ft_putstr(" ");
	}
}

int	ft_echo(t_msh *msh, int cmd_id)
{
	int	i;
	int	print;
	int	flag;

	i = 0;
	print = 0;
	flag = 0;
	if (!msh->cmd[cmd_id].param[1])
	{
		printf("\n");
		return (0);
	}
	while (is_flag(msh->cmd[cmd_id].param[i++]))
		flag = 1;
	while (msh->cmd[cmd_id].param[i])
	{
		print = 1;
		echo_print(msh, cmd_id, print, i);
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
