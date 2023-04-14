/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/14 23:14:20 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*copy_with_value(t_msh *msh, char *expanded, t_parse p, int cursor)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(expanded) + \
	ft_strlen(p.line) - p.arg_sz) + 1);
	if (!str)
		return (error_manager(msh, MALLOC_ERR), NULL);
	while (++i < cursor - 1)
		str[i] = p.line[i];
	while (j < (int)ft_strlen(expanded))
		str[i++] = expanded[j++];
	while (i < (int)ft_strlen(p.line) + (int)ft_strlen(expanded) - p.arg_sz)
		str[i++] = p.line[cursor++ + p.arg_sz];
	str[i] = '\0';
	return (str);
}

char	*expanded_if_isnt_num(t_parse *p, int cur, char *expanded)
{
	p->arg_sz = 1;
	p->i++;
	if (p->line[cur] == '?')
		expanded = ft_itoa(g_status);
	else if (!is_alpha(p->line[cur]))
	{
		p->arg_sz = 0;
		expanded = "$";
	}
	return (expanded);
}

char	*replace_env_arg(t_msh *msh, t_parse *p, int *cursor, int in_q)
{
	char	*expanded;
	char	*str;
	int tmp;

	expanded = NULL;
	if (in_q)
		p->i = *cursor;
	tmp = *cursor + 1;
	if (is_alpha(p->line[tmp]))
		expanded = get_expanded(msh, p, tmp);
	else if (p->line[tmp] == '\'' || p->line[tmp] == '"')
	{
		p->arg_sz = 0;
		if (in_q == 1)
			expanded = "$";
	}
	else if (!is_num(p->line[tmp]))
		expanded = expanded_if_isnt_num(p, tmp, expanded);
	else if (is_num(p->line[tmp]))
		p->arg_sz = 1;
	printf("expanded : %s\n", expanded);
	str = copy_with_value(msh, expanded, *p, tmp);
	if (in_q == 0)
		str = replace_spaces_of_expanded(*p, str);
	printf("str : %s, p->i : %d, p->end_q : %d\n", str, p->i, p->end_q);
	actualize_ind(p, expanded, str, in_q);
	printf("str : %s, p->i : %d, p->end_q : %d\n", str, p->i, p->end_q);
	if (p->line[tmp] == '?')
		free(expanded);
	if (in_q)
		*cursor += ft_strlen(expanded) - 1;
	printf("str : %s\n", str);
	return (free(p->line), str);
}

int	go_to_end_of_arg(int i, char *line, char q, int s)
{
	while (line[i] && !is_end_of_arg(i, line, q, s))
		i++;
	return (i);
}



char	*get_dollar(t_msh *msh, t_parse *p, int *has_dollar)
{
	int	cursor;
	
	cursor = p->strt;
	while (p->line[cursor] && cursor != p->end_q)
	{
		if (p->line[cursor] == '$')
		{
			p->line = replace_env_arg(msh, p, &cursor, 1);
			*has_dollar = 1;
			printf("new end : %d\n", p->end_q);
			printf("new cursor : %d\n", cursor);
		}
		if (p->line[cursor])
			cursor++;
	}
	return (p->line);
}
