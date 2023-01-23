/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:37:28 by colas             #+#    #+#             */
/*   Updated: 2023/01/20 14:31:32 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include "ft_err_printf/ft_printf.h"

int	check_param(t_pipex *ppx, char *param)
{
	char	*pathing;
	char	*slashed;
	int		i;

	if (param == NULL)
		return (ft_err_printf("msh: permission denied:\n"), 2);
	i = 0;
	while (ppx->paths[i])
	{
		slashed = ft_ppx_strjoin(ppx->paths[i], "/");
		pathing = ft_ppx_strjoin(slashed, param);
		free(slashed);
		if (access(pathing, F_OK) == 0)
			return (free(pathing), 0);
		free(pathing);
		i++;
	}
	return (1);
}

char	*get_pathing(t_pipex ppx, int j)
{
	char	*slashed;
	char	*pathing;
	int i;

	i = 0;
	while (ppx.paths[i])
	{
		slashed = ft_ppx_strjoin(ppx.paths[i], "/");
		pathing = ft_ppx_strjoin(slashed, ppx.cmd[j].param[0]);
		free(slashed);
		if (access(pathing, 0) == 0)
			return (pathing);
		free(pathing);
		i++;
	}
	return (NULL);
}

void	get_check_cmds_between(t_pipex *ppx, char **argv)
{
	int	i;
	int j;

	i = 3;
	j = 1;
	while (j < ppx->cmd_nbr)
	{
		ppx->cmd[j].param = ft_split(argv[i], ' ');
		if (!ppx->cmd[j].param)
			return (free_all(ppx->cmd->param));
		if (check_param(ppx, ppx->cmd[j].param[0]) == 1)
			ft_err_printf("msh: command not found: %s\n", ppx->cmd[j].param[0]);
		i++;
		j++;
	}
}

void	check_input(t_pipex *ppx, char **argv)
{
	if	(ppx->infile)
		ppx->input = open(argv[1], O_RDONLY);
	else
		ppx->input = 0;
	if (ppx->input == -1)
	{
		if (access(argv[1], F_OK) == 0)
			ft_err_printf("msh: permission denied: %s\n", argv[1]);
		else
			ft_err_printf("msh: no such file or directory: %s\n", argv[1]);
		return ;
	}
	ppx->cmd[0].param = ft_split(argv[2], ' ');
	if (!ppx->cmd[0].param)
		return ;
	if (check_param(ppx, ppx->cmd[0].param[0]) == 1)
		ft_err_printf("msh: command not found: %s\n", ppx->cmd->param[0]);
}

void	check_output(t_pipex *ppx, char **argv, int argc)
{
	if (ppx->outfile)
		ppx->output = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		ppx->output = 1;
	if (ppx->output == -1)
	{
		ft_err_printf("msh: permission denied: %s\n", argv[argc - 1]);
		return ;
	}
	ppx->cmd[ppx->cmd_nbr - 1].param = ft_split(argv[argc - 2], ' ');
	if (!ppx->cmd[ppx->cmd_nbr - 1].param)
		return (free_all(ppx->cmd->param));
}

int	check_hub(t_pipex *ppx, char **argv, int argc)
{
	//provisoire
	ppx->cmd_nbr = argc - 3;
	ppx->cmd = malloc(sizeof(t_args) * ppx->cmd_nbr);
	if (!ppx->cmd)
		return (0);
	check_input(ppx, argv);
	get_check_cmds_between(ppx, argv);
	check_output(ppx, argv, argc);
	return (1);
}
