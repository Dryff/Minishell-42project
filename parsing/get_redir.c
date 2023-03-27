/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:03:09 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/27 20:05:40 by colas            ###   ########.fr       */
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

int	arrow_is_at_start(t_msh *msh, t_parse p)
{
	while (p.i > 0 && (p.line[p.i] == '>' || p.line[p.i] == '<'))
		p.i--;
	while (p.i > 0  && p.line[p.i] != '|')
	{
		if (!is_white_space(p.line[p.i]))
			return (0);
		p.i--;
	}
	return (1);
}

int	get_name_after_arrow(t_msh *msh, t_parse *p)
{
	int end;
	int	is_in_quotes;
	int	start_quote;
	
	start_quote = 0;
	is_in_quotes = 0;
	while (p->line[p->i] == '<' || p->line[p->i] == '>')
		p->i++;
	while (p->line[p->i] && is_white_space(p->line[p->i]))
		p->i++;
	end = p->i;
	while (p->line[end])
	{
		if ((p->line[end] == '|' || p->line[end] == '>' || \
		p->line[end] == '<') && !is_in_quotes)
			break ;
		quote_check(p->line, end, &start_quote, &is_in_quotes);
		end++;
	}
	return (end - p->i);
}



void	get_name(t_msh *msh, t_parse p, int mode, int cmd_ind)
{
	int	size;

	// if (!arrow_is_at_start(msh, *p))
	size = get_name_after_arrow(msh, &p);
	// printf("size : %d, %s\n",size, &p.line[p.i]);
	if (mode == 0)
		msh->cmd[cmd_ind].ip.in_name = ft_substr(p.line, p.i, size);
	else
	{
		msh->cmd[cmd_ind].op[msh->redir_id].out_name \
		= ft_substr(p.line, p.i, size);
		msh->redir_id++;
	}
}

void	go_after_fd_name(t_msh *msh, t_parse *p)
{
	int	is_in_quotes;
	int	start_quote;

	is_in_quotes = 0;
	start_quote = 0;
	while (p->line[p->i] && (p->line[p->i] == '>' || p->line[p->i] == '<'))
		p->i++;
	while (p->line[p->i])
	{
		if ((p->line[p->i] == '|' || p->line[p->i] == '>' \
		|| p->line[p->i] == '<') && !is_in_quotes)
			break ;
		quote_check(p->line, p->i, &start_quote, &is_in_quotes);
		p->i++;
	}
}

char	*remove_fd_name_and_arrow(t_msh *msh, t_parse p)
{
	char	*str;
	int		j;
	int		i;
	
	str = malloc(sizeof(char) * ft_strlen(p.line) + 1);
	if (!str)
		return (error_manager(msh, MALLOC_ERR), NULL);
	i = 0;
	j = 0;
	while (i < p.i)
	{
		str[j] = p.line[i];
		j++;
		i++;
	}
	go_after_fd_name(msh, &p);
	while (p.i < ft_strlen(p.line))
	{
		str[j] = p.line[p.i];
		j++;
		p.i++;
	}
	str[j] = '\0';
	return (str);
}

int	go_to_end_of_name_and_arrow(t_msh *msh, t_parse p)
{
	int end;
	int	is_in_quotes;
	int	start_quote;
	
	is_in_quotes = 0;
	start_quote = 0;
	end = p.i;
	while (p.line[end])
	{
		if ((p.line[end] == '>' || p.line[end] == '|') && !is_in_quotes)
			break ;
		quote_check(p.line, end, &start_quote, &is_in_quotes);
		end++;
	}
	return (end);
}

void	get_redir(t_msh *msh, t_parse *p, int cmd_index)
{
	if (p->line[p->i] == '>')
	{
		msh->cmd[cmd_index].op[msh->redir_id].output = 1;
		if (p->line[p->i + 1] == '>')
			msh->cmd[cmd_index].op[msh->redir_id].output = 2;
		get_name(msh, *p, 1, cmd_index);
	}
	else if (p->line[p->i] == '<')
	{
		msh->cmd[cmd_index].ip.input = 1;
		if (p->line[p->i + 1] == '<')
			msh->cmd[cmd_index].ip.input = 2;
		get_name(msh, *p, 0, cmd_index);
	}
	p->line = remove_fd_name_and_arrow(msh, *p);
	p->i--;
}
