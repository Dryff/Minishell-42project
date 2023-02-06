/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:53:02 by colas             #+#    #+#             */
/*   Updated: 2023/02/02 14:14:15 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*path_finder(char **envp)
{
	size_t	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (&envp[i][5]);
}

char	**get_paths(char **envp)
{
	char	*raw_paths;
	char	**paths;

	raw_paths = path_finder(envp);
	paths = ft_split(raw_paths, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_pathing(t_msh msh, int j)
{
	char	*slashed;
	char	*pathing;
	int i;

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