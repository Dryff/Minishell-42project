/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:05:55 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/15 00:12:56 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	plus_export(t_msh *msh, char *cmd)
{
	char	*purecmd;
	char	*dup;

	dup = ft_substr(cmd, 0, ft_strlen_until(cmd, '=') - 1);
	if (!dup)
		return (msh->error = 1, 0);
	purecmd = ft_expand(&msh->env, dup);
	if (!purecmd)
		complete_export(msh, cmd);
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
	free(dup);
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
	free(dup2);
	free(dup3);
}
