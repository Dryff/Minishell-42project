/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/15 02:04:01 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*copy_with_value(char *expanded, t_parse p, int cursor)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(expanded) + \
	ft_strlen(p.line) - p.arg_sz) + 1);
	if (!str)
		return (exit(1), NULL);
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

char	*get_str(t_parse *p, int in_q, char *expanded, int tmp)
{
	char	*str;

	str = copy_with_value(expanded, *p, tmp);
	if (in_q == 0)
		str = replace_spaces_of_expanded(*p, str);
	return (str);
}

char	*ext_repl_env_arg(t_parse *p, int in_q, char *expanded)
{
	p->arg_sz = 0;
	if (in_q == 1)
		expanded = "$";
	return (expanded);
}

char	*replace_env_arg(t_msh *msh, t_parse *p, int *cursor, int in_q)
{
	char	*expanded;
	char	*str;
	int		tmp;

	expanded = NULL;
	if (in_q)
		p->i = *cursor;
	tmp = *cursor + 1;
	if (is_alpha(p->line[tmp]))
		expanded = get_expanded(msh, p, tmp);
	else if (p->line[tmp] == '\'' || p->line[tmp] == '"')
		expanded = ext_repl_env_arg(p, in_q, expanded);
	else if (!is_num(p->line[tmp]))
		expanded = expanded_if_isnt_num(p, tmp, expanded);
	else if (is_num(p->line[tmp]))
		p->arg_sz = 1;
	str = get_str(p, in_q, expanded, tmp);
	actualize_ind(p, expanded, str, in_q);
	if (p->line[tmp] == '?')
		free(expanded);
	if (in_q)
		*cursor += ft_strlen(expanded) - 1;
	return (free(p->line), str);
}
