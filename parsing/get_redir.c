/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:03:09 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/26 13:02:41 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*rm_ten(t_msh *msh, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 10)
			str[i] = ' ';
		i++;
	}
	return (str);
}

void	get_name(t_msh *msh, t_parse p, int mode, int cmd_ind)
{
	int	end;
	int	is_in_quotes;
	int	start_quote;

	start_quote = 0;
	while (p.line[p.i] == '<' || p.line[p.i] == '>')
		p.i++;
	while (p.line[p.i] && is_white_space(p.line[p.i]))
		p.i++;
	end = p.i;
	while (p.line[end])
	{
		if (p.line[end] == '|' && !is_in_quotes)
			break ;
		quote_check(p.line, end, &start_quote, &is_in_quotes);
		end++;
	}
	end++;
	// printf("p.i=%d, %s, end=%d\n---\n", p.i, &p.line[p.i], end);
	if (mode == 0)
		msh->cmd[cmd_ind].fd.in_name = rm_ten(msh, quotes_dollars_and_redir \
		(msh, ft_substr(p.line, p.i, end - p.i), cmd_ind));
	else
		msh->cmd[cmd_ind].fd.out_name = rm_ten(msh, quotes_dollars_and_redir \
		(msh, ft_substr(p.line, p.i, end - p.i), cmd_ind));
}

char	*remove_fd_name_and_arrow(t_msh *msh, t_parse *p)
{
	char	*str;
	int		j;
	int		i;

	printf("mysize : %d\n", p->i);
	str = malloc(sizeof(char) * p->i + 1);
	if (!str)
		return (error_manager(msh, MALLOC_ERR), NULL);
	i = 0;
	j = 0;
	while (i < p->i)
	{
		str[j] = p->line[i];
		j++;
		i++;
	}
	str[j] = '\0';
	// printf("str : %s\n", str);
	free(p->line);
	return (str);
}

void	get_redir(t_msh *msh, t_parse *p, int cmd_index)
{
	if (p->line[p->i] == '>' && p->line[p->i + 1] != '>')
	{
		msh->cmd[cmd_index].fd.output = 1;
		get_name(msh, *p, 1, cmd_index);
	}
	else if (p->line[p->i] == '<' && p->line[p->i + 1] != '<')
	{
		msh->cmd[cmd_index].fd.input = 1;
		get_name(msh, *p, 0, cmd_index);
	}
	else if (p->line[p->i] == '>' && p->line[p->i + 1] == '>')
	{
		msh->cmd[cmd_index].fd.output = 2;
		get_name(msh, *p, 1, cmd_index);
	}
	else if (p->line[p->i] == '<' && p->line[p->i + 1] == '<')
	{
		msh->cmd[cmd_index].fd.input = 2;
		get_name(msh, *p, 0, cmd_index);
	}
	p->line = remove_fd_name_and_arrow(msh, p);
}
