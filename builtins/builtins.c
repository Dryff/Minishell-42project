/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:49:30 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/09 11:18:28 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	ft_echo(t_msh *msh, int dash_n)
{
	int		i;
	char	*echo_line;

	echo_line = ft_strnstr(msh->line, "echo", strlen(msh->line));
	i = 4;
	while ((echo_line[i] >= 9 && echo_line[i] <= 13) || echo_line[i] == ' ')
		i++;
	if (dash_n == 0)
		while (echo_line[i] == '-' || echo_line[i] == 'n')
			i++;
	while ((echo_line[i] >= 9 && echo_line[i] <= 13) || echo_line[i] == ' ')
		i++;
	while (echo_line[i])
		printf("%c", echo_line[i++]);
	if (dash_n == 1)
		printf("\n");
	return (0);
}

int	exec_builtin_cmd(t_msh *msh)
{
	if (search_cmd(msh->line, "pwd"))
		return (ft_pwd(), 1);
	else if (search_cmd(msh->line, "echo"))
	{	
		if (search_cmd(msh->line, "-n"))
			return (ft_echo(msh, 0), 1);
		else
			return (ft_echo(msh, 1), 1);
	}
	else if (search_cmd(msh->line, "cd"))
	{	
	}
	else if (search_cmd(msh->line, "env"))
		return (ft_print_env(msh), 1);
	else if (search_cmd(msh->line, "export"))
		return (ft_export(&msh->env, get_export_cmd(msh->line)), 1);
	else if (search_cmd(msh->line, "unset"))
		return (ft_unset(&msh->env, get_unset_cmd(msh->line)), 1);
	else if (search_cmd(msh->line, "var"))
		return (ft_expand(&msh->env, get_expand_cmd(msh->line)), 1);
	return (0);
}
