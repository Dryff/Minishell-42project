/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:03:09 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/22 11:52:31 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void get_name(t_msh *msh, t_parse p, int mode)
{
	int     end;
    int		is_in_quotes;
	int		start_quote;
	
	while (msh->line[p.i] == '<' || msh->line[p.i] == '>')
		p.i++;
	while (msh->line[p.i] && is_white_space(msh->line[p.i]))
		p.i++;
	end = p.i;
	while (msh->line[end])
    {
        if (msh->line[end] == '|' && is_in_quotes)
            break;
		quote_check(msh->line, end, &start_quote, &is_in_quotes);
        end++;
    }
		end++;
	if (mode == 0)
    {
		msh->fildes.in_name = ft_substr(msh->line, p.i, end - p.i);
        printf("in : %s\n", msh->fildes.in_name);
    }
	else
    {
		msh->fildes.out_name = ft_substr(msh->line, p.i, end - p.i);
        printf("out : %s\n", msh->fildes.out_name);    
    }
}

void	get_redir(t_msh *msh, t_parse *p, int cmd_index)
{
	if (p->line[p->i] == '>' && p->line[p->i + 1] != '>')
    {
		msh->cmd[cmd_index].fd.output = 1;
	    get_name(msh, *p, 1);
    }
	else if (p->line[p->i] == '<' && p->line[p->i + 1] != '<')
	{
		msh->cmd[cmd_index].fd.input = 1;
	    get_name(msh, *p, 0);
    }
	else if (p->line[p->i] == '>' && p->line[p->i + 1] == '>')
	{
		msh->cmd[cmd_index].fd.output = 2;
	    get_name(msh, *p, 1);
        p->i++;
    }
	else if (p->line[p->i] == '<' && p->line[p->i + 1] == '<')
	{
		msh->cmd[cmd_index].fd.input = 2;
	    get_name(msh, *p, 0);
        p->i++;
    }
}