/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:05:55 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/21 00:19:44 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	simple_plus_export(t_msh *msh, char *cmd)
{
	char	*dup;
	char	*dup2;

	dup = ft_substr(cmd, 0, ft_strlen_until(cmd, '=') - 1);
	dup2 = ft_strjoin(dup, "=");
	if (!dup || !dup2)
		exit(1);
	if (get_position(msh->env.tab, dup) == -1)
		complete_export(msh, dup2);
	free(dup);
	free(dup2);
}

char	*get_plus_export_cmd(char *cmd)
{
	char	*dup;
	char	*dup2;
	char	*dup3;

	dup = ft_substr(cmd, 0, ft_strlen_until(cmd, '=') - 1);
	if (!dup)
		return (NULL);
	dup2 = ft_strjoin(dup, "=");
	if (!dup2)
		return (NULL);
	dup3 = ft_substr(cmd, ft_strlen_until(cmd, '=') + 1, ft_strlen(cmd));
	if (!dup3)
		return (NULL);
	free(dup);
	dup = ft_strjoin(dup2, dup3);
	if (!dup)
		return (NULL);
	free(dup2);
	free(dup3);
	return (dup);
}

int	plus_export(t_msh *msh, char *cmd)
{
	char	*purecmd;
	char	*dup;
	char	*export_cmd;

	if (!cmd[ft_strlen_until(cmd, '=') + 1])
		return (simple_plus_export(msh, cmd), 1);
	dup = ft_substr(cmd, 0, ft_strlen_until(cmd, '=') - 1);
	if (!dup)
		return (msh->error = 1, 0);
	purecmd = ft_expand(&msh->env, dup);
	if (!purecmd)
	{
		export_cmd = get_plus_export_cmd(cmd);
		if (!export_cmd)
			return (msh->error = 1, 0);
		complete_export(msh, export_cmd);
		free(export_cmd);
	}
	else
		actual_plus_export(msh, dup, cmd, purecmd);
	free(dup);
	return (1);
}

void	actual_plus_export(t_msh *msh, char *dup, char *cmd, char *purecmd)
{
	char	*dup2;
	char	*dup3;

	dup2 = ft_strjoin(dup, "=");
	if (!dup2)
		exit(1);
	dup = ft_strjoin(dup2, purecmd);
	if (!dup)
		exit(1);
	dup3 = ft_substr(cmd, ft_strlen_until(cmd, '=') + 1, ft_strlen(cmd));
	if (!dup3)
		exit(1);
	free(dup2);
	dup2 = ft_strjoin(dup, dup3);
	if (!dup2)
		exit(1);
	complete_export(msh, dup2);
	free(dup);
	free(dup2);
	free(dup3);
}
