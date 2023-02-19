/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:22:55 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/19 14:12:38 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	ft_dvd(t_msh *msh, int cmd_id)
{
	char	*actual_path;
	char	*new_path;

	printf("\ncmd = %s\n", msh->cmd[cmd_id].param[1]);
	if (!msh->cmd[cmd_id].param[1])
	{
		if (chdir(ft_expand(&msh->env, "HOME")) != 0)
		{
			perror("chdir");
			exit(1);
		}
	}
	else
	{
		actual_path = getcwd(NULL, 0);
		new_path = ft_strjoin(actual_path, "/");
		new_path = ft_strjoin(new_path, msh->cmd[cmd_id].param[1]);
		if (chdir(new_path) != 0)
			perror("chdir");
	}
}
