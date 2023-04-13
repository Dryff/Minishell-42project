/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/13 22:41:11 by mfinette         ###   ########.fr       */
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

char	*replace_env_arg(t_msh *msh, t_parse *p, int cursor, int mode)
{
	char	*expanded;
	char	*str;

	expanded = NULL;
	cursor++;
	if (is_alpha(p->line[cursor]))
		expanded = get_expanded(msh, p, cursor);
	else if (p->line[cursor] == '\'' || p->line[cursor] == '"')
	{
		p->arg_sz = 0;
		if (mode == 1)
			expanded = "$";
	}
	else if (!is_num(p->line[cursor]))
		expanded = expanded_if_isnt_num(p, cursor, expanded);
	else if (is_num(p->line[cursor]))
		p->arg_sz = 1;
	str = copy_with_value(msh, expanded, *p, cursor);
	str = replace_spaces_of_expanded(*p, str);
	actualize_ind(p, expanded, str);
	if (p->line[cursor] == '?')
		free(expanded);
	return (free(p->line), str);
}

char	*get_dollar(t_msh *msh, t_parse *p)
{
	int	cursor;
	int	end_quote_pos;

	cursor = p->strt + 1;
	end_quote_pos = go_to_end_quote(cursor, p->line, p->q, p->strt);
	// printf("end_quote pos : %d\n", end_quote_pos);
	while (p->line[cursor] && cursor != end_quote_pos)
	{
		if (p->line[cursor] == '$' && p->q == '"')
		{
			// printf("avant : %s\n", &p->line[cursor]);
			p->line = replace_env_arg(msh, p, cursor, 1);
		}
		cursor++;
	}
	return (p->line);
}
