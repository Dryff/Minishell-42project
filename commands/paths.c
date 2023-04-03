/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:53:02 by colas             #+#    #+#             */
/*   Updated: 2023/04/03 08:52:50 by cgelin           ###   ########.fr       */
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

char	**get_paths(char **envp)
{
	char	*raw_paths;
	char	**paths;

	raw_paths = path_finder(envp);
	if (raw_paths == NULL)
		return (NULL);
	paths = ft_split(raw_paths, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*check_slash(t_msh msh, int j)
{
	char *pathing;
	
	if (ft_strchr(msh.cmd[j].param[0], '/'))
	{
		pathing = msh.cmd[j].param[0];
		if (access(pathing, 0) == 0)
			return (pathing);
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
