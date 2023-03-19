/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:22:55 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/19 16:57:23 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

#define OLD 1
#define HOME 2

void	update_old_pwd(t_msh *msh, char *actual_path)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", actual_path);
	complete_export(msh, oldpwd);
	free(oldpwd);
	free(actual_path);
}

void	chdir_home_old(t_msh *msh, int code)
{
	int		error;
	char	*actual_path;
	
	error = 0;
	actual_path = getcwd(NULL, 0);
	if (code == HOME)
	{
		if (chdir(ft_expand(&msh->env, "HOME")) != 0)
		{
			error = 1;
			perror("chdir");
			msh->status = 1;
		}
	}
	else if (code == OLD)
	{
		if (chdir(ft_expand(&msh->env, "OLDPWD")) != 0)
		{
			error = 1;
			perror("chdir");
			msh->status = 1;
		}
	}
	if (!error)
		update_old_pwd(msh, actual_path);
}

void	ft_dvd(t_msh *msh, int cmd_id)
{
	char	*actual_path;
	char	*new_path;
	char	*tmp;

	if (!msh->cmd[cmd_id].param[1])
		chdir_home_old(msh, HOME);
	else if (msh->cmd[cmd_id].param[1][0] == '-')
		chdir_home_old(msh, OLD);
	else
	{
		actual_path = getcwd(NULL, 0);
		new_path = ft_strjoin(actual_path, "/");
		tmp = ft_strjoin(new_path, msh->cmd[cmd_id].param[1]);
		if (chdir(tmp) != 0)
		{
			perror("chdir");
			free(actual_path);
			msh->status = 1;
		}
		else
			update_old_pwd(msh, actual_path);
		free(new_path);
		free(tmp);
	}
}
