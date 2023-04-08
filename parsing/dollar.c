/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/05 14:32:46 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*get_expanded(t_msh *msh, t_parse *p, int cursor)
{
	char	*arg;
	char	*expanded;
	int		k;

	k = cursor;
	// printf("start : %d\n", p->line[k]);
	while (p->line[k] && is_alpha(p->line[k]))
		k++;
	arg = ft_substr(p->line, cursor, k - cursor);
	// printf("arg : %s\n", arg);
	expanded = ft_expand(&msh->env, arg);
	free(arg);
	k -= cursor;
	p->arg_sz = k;
	return (expanded);
}

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

char	*replace_env_arg(t_msh *msh, t_parse *p, int cursor)
{
	char	*expanded;
	char	*str;

	expanded = NULL;
	cursor++;
	if (is_alpha(p->line[cursor]))
		expanded = get_expanded(msh, p, cursor);
	else
	{
		p->arg_sz = 1;
		p->i++;
		if (p->line[cursor] == '?')
			expanded = ft_itoa(msh_status);
		else if (!is_alpha(p->line[cursor]))
			expanded = "$";
	}
	str = copy_with_value(msh, expanded, *p, cursor);
	p->i += ft_strlen(expanded) - p->arg_sz - 1;
	if (p->i < 0)
		p->i = 0;
	if (p->line[cursor] == '?')
		free(expanded);
	return (str = replace_spaces_of_expanded(*p, str), free(p->line), str);
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
			p->line = replace_env_arg(msh, p, cursor);
		}
		cursor++;
	}
	return (p->line);
}
