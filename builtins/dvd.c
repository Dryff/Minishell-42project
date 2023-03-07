/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:22:55 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/07 14:42:17 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	ft_dvd(t_msh *msh, int cmd_id)
{
	char	*oldpwd;
	char	*actual_path;
	char	*new_path;
	char	*tmp;

	if (!msh->cmd[cmd_id].param[1])
	{
		if (chdir(ft_expand(&msh->env, "HOME")) != 0)
		{
			actual_path = getcwd(NULL, 0);
			oldpwd = ft_strjoin("OLDPWD=", actual_path);
			complete_export(msh, oldpwd);
			free(oldpwd);
			free(actual_path);		
			perror("chdir");
			exit(1);
		}
	}
	else if (msh->cmd[cmd_id].param[1][0] == '-')
	{
		if (chdir(ft_expand(&msh->env, "OLDPWD")) != 0)
		{
			perror("chdir");
			exit(1);
		}
	}
	else
	{
		actual_path = getcwd(NULL, 0);
		oldpwd = ft_strjoin("OLDPWD=", actual_path);
		complete_export(msh, oldpwd);
		new_path = ft_strjoin(actual_path, "/");
		tmp = ft_strjoin(new_path, msh->cmd[cmd_id].param[1]);
		if (chdir(tmp) != 0)
			perror("chdir");
		free(new_path);
		free(actual_path);
		free(tmp);
		free(oldpwd);
	}
}
