/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:53:02 by colas             #+#    #+#             */
/*   Updated: 2023/02/22 16:48:49 by mfinette         ###   ########.fr       */
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

char	*get_pathing(t_msh msh, int j)
{
	char	*slashed;
	char	*pathing;
	int		i;

	i = 0;
	while (msh.paths[i])
	{
		slashed = ft_strjoin(msh.paths[i], "/");
		pathing = ft_strjoin(slashed, msh.cmd[j].param[0]);
		free(slashed);
		if (access(pathing, 0) == 0)
			return (pathing);
		free(pathing);
		i++;
	}
	return (NULL);
}
