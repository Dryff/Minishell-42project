/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:03:09 by cgelin            #+#    #+#             */
/*   Updated: 2023/03/24 13:23:09 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

// char    *rm_previous_quotes(char *str, int start_quote, int end, int *quote_rm_count)
// {
//     int j;
//     int i;
//     char    *res;

//     res = malloc(sizeof(char) * ft_strlen(str) + 1);
//     if (!res)
//         return (NULL);
//     i = 0;
//     j = -1;
// 	while (++j < start_quote)
// 		res[j] = str[j];
// 	i = j;
// 	while (str[j] && j <= end)
// 	{
// 		if (str[j] != str[start_quote])
//         {
// 			res[i++] = str[j];
//             *quote_rm_count += 1;
//         }
// 		j++;
// 	}
// 	while (str[j])
// 		res[i++] = str[j++];
// 	free(str);
//     return (res[i] = '\0', res);
// }

// char    *search_quotes_and_rm(t_msh *msh, char *str)
// {
//     int i;
//     char *res;
//     int start_quote;
//     int is_in_quotes;
//     int quote_rm_count;

//     i = 0;
//     start_quote = 0;
//     is_in_quotes = 0;
//     while (str[i])
//     {
//         quote_rm_count = 0;
//         quote_check(str, i, &start_quote, &is_in_quotes);
//         printf("start_quotes : %d, i : %d, %s\n", start_quote, i, str);
//         if (is_end_quote(str, start_quote, i))
//         {
//             str = quotes_dollars_and_redir(str, start_quote, i, &quote_rm_count);
//             i -= quote_rm_count;
//         }
//         if (str[i])
//             i++;
//     }
//     return (str);
// }

char *replace_ten_by_spaces(t_msh *msh, char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == 10)
            str[i] = ' ';
        i++;
    }
    return (str);
}

void get_name(t_msh *msh, t_parse p, int mode, int cmd_index)
{
	int     end;
    int		is_in_quotes;
	int		start_quote;
	
    start_quote = 0;
	while (p.line[p.i] == '<' || p.line[p.i] == '>')
		p.i++;
	while (p.line[p.i] && is_white_space(p.line[p.i]))
		p.i++;
	end = p.i;
	while (p.line[end])
    {
        if (p.line[end] == '|' && !is_in_quotes)
            break;
		quote_check(p.line, end, &start_quote, &is_in_quotes);
        end++;
    }
	end++;
    // printf("p.i=%d, %s, end=%d\n---\n", p.i, &p.line[p.i], end);
	if (mode == 0)
    {
		msh->cmd[cmd_index].fd.in_name = replace_ten_by_spaces(msh, quotes_dollars_and_redir(msh, ft_substr(p.line, p.i, end - p.i), cmd_index));
		printf("in = %s\n", msh->cmd[cmd_index].fd.in_name);
    }
	else
    {
		msh->cmd[cmd_index].fd.out_name = replace_ten_by_spaces(msh, quotes_dollars_and_redir(msh, ft_substr(p.line, p.i, end - p.i), cmd_index));
		printf("out = [%s]\n", msh->cmd[cmd_index].fd.out_name);
    }
}

char    *remove_fd_name_and_arrow(t_msh *msh, t_parse *p)
{
    char *str;
    int j;
    int i;

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