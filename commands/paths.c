/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:53:02 by colas             #+#    #+#             */
/*   Updated: 2023/04/13 16:45:43 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*path_finder(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4))
		i++;
	if (!env[i])
		return (NULL);
	return (&env[i][5]);
}

char	**get_paths(t_msh *msh, char **envp)
{
	char	*raw_paths;
	char	**paths;

	raw_paths = path_finder(envp);
	if (raw_paths == NULL)
		return (NULL);
	paths = ft_split(raw_paths, ':');
	if (!paths)
		return (free(msh->line), exit(1), NULL);
	return (paths);
}

char	*check_slash(t_msh msh, int j)
{
	struct stat	path_stat;

	if (ft_strchr(msh.cmd[j].param[0], '/'))
	{
		path_stat.st_mode = 0;
		stat(msh.cmd[j].param[0], &path_stat);
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_err_printf("msh: %s: Is a directory\n", msh.cmd[j].param[0]);
			g_status = 126;
			return (msh.cmd[j].param[0]);
		}
		if (access(msh.cmd[j].param[0], 0) == 0)
			return (msh.cmd[j].param[0]);
	}
	return (NULL);
}

char	*get_pathing(t_msh msh, int j)
{
	char	*slashed;
	char	*pathing;
	int		i;

	i = 0;
	pathing = check_slash(msh, j);
	if (pathing)
		return (pathing);
	if (!msh.paths)
		return (NULL);
	while (msh.paths[i])
	{
		slashed = ft_strjoin(msh.paths[i], "/");
		if (!slashed)
			return (NULL);
		pathing = ft_strjoin(slashed, msh.cmd[j].param[0]);
		if (!slashed)
			return (NULL);
		free(slashed);
		if (access(pathing, 0) == 0)
			return (pathing);
		free(pathing);
		i++;
	}
	return (NULL);
}
