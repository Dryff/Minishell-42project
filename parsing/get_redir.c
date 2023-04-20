/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:03:09 by cgelin            #+#    #+#             */
/*   Updated: 2023/04/20 15:07:38 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_name_after_arrow(t_msh *msh, t_parse *p)
{
	int	end;
	int	is_in_quotes;
	int	start_quote;

	(void)msh;
	start_quote = 0;
	is_in_quotes = 0;
	while (p->line[p->i] == '<' || p->line[p->i] == '>')
		p->i++;
	while (p->line[p->i] && is_white_space(p->line[p->i]))
		p->i++;
	end = p->i;
	while (p->line[end])
	{
		if ((p->line[end] == '|' || p->line[end] == '>' || p->line[end] == '<' || p->line[end] == 10) && !is_in_quotes)
			break ;
		quote_check(p->line, end, &start_quote, &is_in_quotes);
		end++;
	}
	return (end - p->i);
}

void	get_name(t_msh *msh, t_parse p, int mode, int cmd_ind)
{
	int		size;
	char	*sub;

	size = get_name_after_arrow(msh, &p);
	if (mode == 0)
	{
		sub = ft_substr(p.line, p.i, size);
		printf("sub = %s\n", sub);
		if (msh->cmd[cmd_ind].ip.input == 2)
			handle_here_doc(msh, sub, cmd_ind);
		if (msh->cmd[cmd_ind].ip.input == 1)
			msh->cmd[cmd_ind].ip.in_name[msh->in_id++] = \
			develop_name(msh, sub, 0);
	}
	else
	{
		sub = ft_substr(p.line, p.i, size);
		msh->cmd[cmd_ind].op[msh->out_id].out_name \
		= develop_name(msh, sub, 0);
		msh->out_id++;
	}
}

void	go_after_fd_name(t_msh *msh, t_parse *p, int cmd_id)
{
	int	is_in_quotes;
	int	start_quote;

	(void)cmd_id;
	(void)msh;
	is_in_quotes = 0;
	start_quote = 0;
	while (p->line[p->i] && (p->line[p->i] == '>' || p->line[p->i] == '<'))
		p->i++;
	while (p->line[p->i] && is_white_space(p->line[p->i]))
		p->i++;
	while (p->line[p->i])
	{
		if ((p->line[p->i] == '|' || p->line[p->i] == '>' \
		|| p->line[p->i] == '<' || p->line[p->i] == 10) && !is_in_quotes)
			break ;
		quote_check(p->line, p->i, &start_quote, &is_in_quotes);
		p->i++;
	}
	while (p->line[p->i] && is_white_space(p->line[p->i]))
		p->i++;
}

char	*remove_fd_name_and_arrow(t_msh *msh, t_parse p, int cmd_id)
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
	go_after_fd_name(msh, &p, cmd_id);
	while (p.i < (int)ft_strlen(p.line))
	{
		str[j] = p.line[p.i];
		j++;
		p.i++;
	}
	str[j] = '\0';
	free(p.line);
	return (str);
}

void	get_redir(t_msh *msh, t_parse *p, int cmd_index)
{
	if (p->line[p->i] == '>')
	{
		if (msh->cmd[cmd_index].op)
			msh->cmd[cmd_index].op[msh->out_id].output = 1;
		if (p->line[p->i + 1] == '>')
			msh->cmd[cmd_index].op[msh->out_id].output = 2;
		get_name(msh, *p, 1, cmd_index);
	}
	else if (p->line[p->i] == '<')
	{
		msh->cmd[cmd_index].ip.input = 1;
		if (p->line[p->i + 1] == '<')
			msh->cmd[cmd_index].ip.input = 2;
		get_name(msh, *p, 0, cmd_index);
	}
	p->line = remove_fd_name_and_arrow(msh, *p, cmd_index);
	printf("p->line = %s\n", p->line);
	p->i--;
}
