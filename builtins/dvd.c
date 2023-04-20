/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:22:55 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/20 16:29:44 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

#define OLD 1
#define HOME 2
#define PWD 3
#define NOCD "msh : cd : "
#define NOP ": No such file or directory\n"

void	update_pwd_env(t_msh *msh, char *actual_path)
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;

	oldpwd = ft_strjoin("OLDPWD=", actual_path);
	tmp = getcwd(NULL, 0);
	if (!oldpwd || !tmp)
		exit(1);
	pwd = ft_strjoin("PWD=", tmp);
	complete_export(msh, pwd);
	complete_export(msh, oldpwd);
	update_msh_status(0);
	free(pwd);
	free(tmp);
	free(oldpwd);
}

void	chdir_home(t_msh *msh)
{
	int		error;
	char	*actual_path;
	char	*tmp;

	error = 0;
	tmp = ft_expand(&msh->env, "HOME");
	actual_path = getcwd(NULL, 0);
	if (!tmp)
	{
		error = 1;
		ft_err_printf("cd: HOME not set\n");
		update_msh_status(1);
	}
	else if (chdir(ft_expand(&msh->env, "HOME")) != 0)
	{
		error = 1;
		ft_err_printf("msh: cd: %s: No such file or directory\n", tmp);
		update_msh_status(1);
	}
	if (!error)
		update_pwd_env(msh, actual_path);
	free(actual_path);
}

void	chdir_old(t_msh *msh)
{
	int		error;
	char	*actual_path;
	char	*tmp;

	error = 0;
	actual_path = getcwd(NULL, 0);
	tmp = ft_expand(&msh->env, "OLDPWD");
	if (!tmp)
	{
		error = 1;
		ft_err_printf("cd: OLDPWD not set\n");
		update_msh_status(1);
	}
	else if (chdir(ft_expand(&msh->env, "OLDPWD")) != 0)
	{
		error = 1;
		ft_err_printf("msh: cd: %s: No such file or directory\n", tmp);
		update_msh_status(1);
	}
	else
		printf("%s\n", ft_expand(&msh->env, "OLDPWD"));
	if (!error)
		update_pwd_env(msh, actual_path);
	free(actual_path);
}

void	real_pwd(t_msh *msh, char *cmd)
{	
	char	*tmp;
	char	*actual_path;
	char	*new_path;

	actual_path = getcwd(NULL, 0);
	if (!actual_path)
		return ((void)cwd_error());
	new_path = ft_strjoin(actual_path, "/");
	tmp = ft_strjoin(new_path, cmd);
	if (chdir(tmp) != 0)
	{
		ft_err_printf("cd: %s: No such file or directory\n", cmd);
		update_msh_status(1);
	}
	else
		update_pwd_env(msh, actual_path);
	free(new_path);
	free(tmp);
	free(actual_path);
}

void	ft_dvd(t_msh *msh, int cmd_id)
{
	char	*cmd;

	cmd = msh->cmd[cmd_id].param[1];
	if (!cmd)
		chdir_home(msh);
	else if (msh->cmd[cmd_id].param[2])
	{
		ft_err_printf("cd: too many arguments\n");
		update_msh_status(1);
		return ;
	}
	else if (cmd[0] == '/')
	{
		if (chdir(cmd) != 0)
		{
			ft_err_printf("%s%s%s", NOCD, cmd, NOP);
			update_msh_status(1);
		}
		return ;
	}
	else if (cmd[0] == '-' && !cmd[1])
		chdir_old(msh);
	else
		real_pwd(msh, cmd);
}
