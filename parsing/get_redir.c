/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:03:09 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/22 16:59:58 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void get_name(t_msh *msh, t_parse p, int mode)
{
	int     end;
    int		is_in_quotes;
	int		start_quote;
	
    start_quote = 0;
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
		msh->fildes.in_name = ft_substr(msh->line, p.i, end - p.i);
	else
		msh->fildes.out_name = ft_substr(msh->line, p.i, end - p.i);
}

// int get_size_of_cmd(t_parse *p)
// {   
//     int count;
//     int	is_in_quotes;
// 	int	start_quote;

//     is_in_quotes = 0;
// 	start_quote = 0;
//     while (p->i > 0)
//     {
//         if (p->line[p->i] == '|' && is_in_quotes)
//             break;
// 		quote_check(p->line, p->i, &start_quote, &is_in_quotes);
//         p->i--;
//     }
//     while (p->line[p->i] && is_white_space(p->line[p->i]))
//         p->i++;
//     count = p->i;
//     while (p->line[count])
//     {
//         printf("p->line counterstrike : %s\n", &p->line[count]);
//         if ((p->line[count] == '<' || p->line[count] == '>') && !is_in_quotes)
//             break;
// 		quote_check(p->line, count, &start_quote, &is_in_quotes);
//         count++;
//     }
//     return (count - p->i);
// }

char    *remove_fd_name_and_arrow(t_parse *p)
{
    char *str;
    int j;
    int i;

    // printf("mysize : %d\n", p->i);
    str = malloc(sizeof(char) * p->i + 1);
    if (!str)
        return (error_manager(MALLOC_ERR), NULL);
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
    return (str);
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
    }
	else if (p->line[p->i] == '<' && p->line[p->i + 1] == '<')
	{
		msh->cmd[cmd_index].fd.input = 2;
	    get_name(msh, *p, 0);
    }
    p->line = remove_fd_name_and_arrow(p);
}