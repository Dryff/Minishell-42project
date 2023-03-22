/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:22:55 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/21 19:34:34 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

#define OLD 1
#define HOME 2

void	update_pwd_env(t_msh *msh, char *actual_path)
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;

	oldpwd = ft_strjoin("OLDPWD=", actual_path);
	tmp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", tmp);
	complete_export(msh, pwd);
	complete_export(msh, oldpwd);
	free(pwd);
	free(tmp);
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
			ft_err_printf("cd: HOME not set\n");
			update_msh_status(1);
		}
	}
	else if (code == OLD)
	{
		if (chdir(ft_expand(&msh->env, "OLDPWD")) != 0)
		{
			error = 1;
			ft_err_printf("cd: OLDPWD not set\n");
			update_msh_status(1);
		}
	}
	if (!error)
		update_pwd_env(msh, actual_path);
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
			ft_err_printf("cd: %s: No such file or directory\n", msh->cmd[cmd_id].param[1]);
			free(actual_path);
			update_msh_status(1);
		}
		else
			update_pwd_env(msh, actual_path);
		free(new_path);
		free(tmp);
	}
}
