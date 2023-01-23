/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:49:30 by cgelin            #+#    #+#             */
/*   Updated: 2023/01/23 19:24:30 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	ft_echo(t_msh msh, int dash_n)
{
	int i;
	char *echo_line;
	
	echo_line = ft_strnstr(msh.line, "echo", strlen(msh.line));
	i = 4;
	while ((echo_line[i] >= 9 && echo_line[i] <= 13) || echo_line[i] == ' ')
		i++;
	if (dash_n == 0)
		while (echo_line[i] == '-' || echo_line[i] == 'n')
			i++;
	while ((echo_line[i] >= 9 && echo_line[i] <= 13) || echo_line[i] == ' ')
		i++;
	while (echo_line[i])
		write(1, &echo_line[i++], 1);
	if (dash_n == 1)
		write(1, "\n", 1);	
	return (0);
}

int	exec_cmd(t_msh msh)
{
	if (search_cmd(msh.line, "pwd"))
		ft_pwd();
	else if (search_cmd(msh.line, "echo"))
	{	
		if (search_cmd(msh.line, "-n"))
			ft_echo(msh, 0);
		else
			ft_echo(msh, 1);
	}
	return (1);
}

int is_builtin(t_msh msh)
{
	if (strncmp(msh.line, "echo", strlen(msh.line)))
		return (1);
	else if (strncmp(msh.line, "pwd", strlen(msh.line)))
		return (1);
	else if (strncmp(msh.line, "cd", strlen(msh.line)))
		return (1);
	else if (strncmp(msh.line, "export", strlen(msh.line)))
		return (1);
	else if (strncmp(msh.line, "unset", strlen(msh.line)))
		return (1);
	else if (strncmp(msh.line, "env", strlen(msh.line)))
		return (1);
	return (0);
}

int	minishell(t_msh *msh)
{
	exec_cmd(*msh);
	return (0);
}
