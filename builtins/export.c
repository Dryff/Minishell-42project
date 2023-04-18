/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laquarium <laquarium@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:36:02 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/18 16:10:36 by laquarium        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	valid_export(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] >= '0' && cmd[i] <= '9')
		return (update_msh_status(1), WRONG_EXPORT);
	while (i < ft_strlen_until(cmd, '=') - 1)
	{
		if (!is_valid_c(cmd[i]))
			return (update_msh_status(1), WRONG_EXPORT);
		i++;
	}
	if (cmd[i] == '+' && cmd[i + 1] == '=')
		return (PLUS_EXPORT);
	else if (!is_valid_c(cmd[i]))
		return (update_msh_status(1), WRONG_EXPORT);
	if (!is_in_charset('=', cmd))
		return (EMPTY_EXPORT);
	return (VALID_EXPORT);
}

void	ft_declare_print(t_env *env)
{
	int	i;
	int	j;
	int	size;

	i = -1;
	size = 0;
	while (env->sort_tab[size])
		size++;
	while (env->sort_tab[++i])
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(env->sort_tab[i], env->sort_tab[j]) > 0)
				ft_strswap(&env->sort_tab[i], &env->sort_tab[j]);
			j++;
		}
	}
	i = -1;
	while (env->sort_tab[++i])
		ft_export_print(env->sort_tab[i]);
}

int	complete_export(t_msh *msh, char *cmd)
{
	int		pos;
	int		sort_pos;
	char	*purecmd;

	purecmd = ft_substr(cmd, 0, ft_strlen_until(cmd, '='));
	if (!purecmd)
		return (msh->error = 1, 0);
	pos = get_position(msh->env.tab, purecmd);
	sort_pos = get_position(msh->env.sort_tab, purecmd);
	if (pos == -1)
		add_export(msh, cmd);
	else if (pos == -2)
		return (msh->error = 1, 0);
	else
		replace_export(msh, cmd, pos);
	if (sort_pos == -1)
		add_invisible_export(msh, cmd);
	else if (sort_pos == -2)
		return (msh->error = 1, 0);
	else
		replace_secret_export(msh, cmd, pos);
	free(purecmd);
	return (1);
}

int	ft_export(t_msh *msh, int cmd_id, int flag)
{
	char	*cmd;
	int		i;

	i = 0;
	if (flag == NOEXEC)
		return (check_export(msh), 0);
	while (msh->cmd[cmd_id].param[i])
		i++;
	if (i < 2)
		ft_declare_print(&msh->env);
	i = 1;
	while (msh->cmd[cmd_id].param[i])
	{
		cmd = msh->cmd[cmd_id].param[i];
		if (valid_export(cmd) == EMPTY_EXPORT)
			add_invisible_export(msh, cmd);
		else if (valid_export(cmd) == VALID_EXPORT)
			complete_export(msh, cmd);
		else if (valid_export(cmd) == PLUS_EXPORT)
			plus_export(msh, cmd);
		if (msh->error)
			exit(1);
		i++;
	}
	return (0);
}
