/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:24 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/21 22:06:26 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	go_to_end_quote(int i, char *line, char q, int s)
{
	while (line[i] && !is_end_of_arg(i, line, q, s))
		i++;
	while (i > 0 && line[i] != q)
		i--;
	return (i);
}

int	go_to_end_of_arg(int i, char *line, char q, int s)
{
	while (line[i] && line[i] == q)
		i++;
	while (line[i] && !is_end_of_arg(i, line, q, s))
		i++;
	return (i);
}

void	quote_handling(t_msh *msh, t_parse *p)
{	
	int q_nbr;
	
	p->q = p->line[p->i];
	p->i = go_to_end_of_arg(p->i, p->line, p->q, p->strt);
	printf("end of arg : %d\n", p->i);
	q_nbr = quote_rm_nbr(*p);
	p->line = get_dollar(msh, p);
	p->line = getline_rm_quote(msh, *p);
	p->i -= q_nbr;
	p->i++;
	printf("p.i bro : %d, pstrt : %d, p.line : %s\n", p->i, p->strt, p->line);
}

void get_name(t_msh *msh, t_parse p, int mode)
{
	int end;
	
	while (msh->line[p.i] == '<' || msh->line[p.i] == '>')
		p.i--;
	while (msh->line[p.i] && is_white_space(msh->line[p.i]))
		p.i--;
	end = p.i;
	while (msh->line[end] && !is_white_space(msh->line[end]))
		end++;
	if (mode == 0)
		msh->fildes.in_name = ft_substr(msh->line, p.i, end - p.i);
	else
		msh->fildes.out_name = ft_substr(msh->line, p.i, end - p.i);
}

void	get_redir(t_msh *msh, t_parse *p, int cmd_index)
{
	if (p->line[p->i] == '>' && p->line[p->i + 1] != '>')
		msh->cmd[cmd_index].fd.input = 1;
	else if (p->line[p->i] == '<' && p->line[p->i + 1] != '<')
		msh->cmd[cmd_index].fd.output = 2;
	else if (p->line[p->i] == '>' && p->line[p->i + 1] == '>')
		msh->cmd[cmd_index].fd.input = 3;
	else if (p->line[p->i] == '<' && p->line[p->i + 1] == '<')
		msh->cmd[cmd_index].fd.output = 4;
	get_name(msh, *p, msh->cmd[cmd_index].fd.output % 2);
}

char	*quotes_dollars_and_redir(t_msh *msh, char *str, int cmd_index, int i)
{
	t_parse	p;

	p.line = str;
	p.i = 0;
	p.strt = 0;
	printf("p.ay = %d\n", p.i);
	while (p.line[p.i])
	{
		if (p.line[p.i] == '"' || p.line[p.i] == '\'')
		{
			p.strt = p.i;
			quote_handling(msh, &p);
			p.line = replace_spaces(p, p.line);
		}
		else if (p.line[p.i] == '>' || p.line[p.i] == '<')
			get_redir(msh, &p, cmd_index);
		else if (p.line[p.i] == '$')
			p.line = replace_env_arg(msh, &p, p.i);
		else
			p.line = replace_spaces(p, p.line);
		if (p.line[p.i])
			p.i++;
	}
	return (p.line);
}
	




