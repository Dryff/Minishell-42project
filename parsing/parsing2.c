/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:24 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/20 02:13:47 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*get_expanded(t_msh *msh, t_parse *p, int cursor)
{
	char	*arg;
	char	*expanded;

	p->j = cursor;
	while (p->line[p->j] && p->line[p->j] != '"' && p->line[p->j] != '\'' \
	&& p->line[p->j] != 10 && p->line[p->j] != ' ' && p->line[p->j] != '$')
		p->j++;
	arg = ft_substr(p->line, cursor, p->j - cursor);
	printf("arg : %s\n", arg);
	expanded = ft_expand(&msh->env, arg);
	free(arg);
	p->j -= cursor;
	return (expanded);
}

char	*copy_with_value(char *str, char *expanded, t_parse p, int cursor)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < cursor - 1)
		str[i] = p.line[i];
	while (j < (int)ft_strlen(expanded))
		str[i++] = expanded[j++];
	while (i < (int)ft_strlen(p.line) + (int)ft_strlen(expanded) - p.j)
		str[i++] = p.line[cursor++ + p.j];
	str[i] = '\0';
	printf("|str : %s|\n", str);
	return (str);
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
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
		expanded = "$";
		p->i++;
		p->j = 1;
	}
	printf("expanded : %s\n", expanded);
	str = malloc(sizeof(char) * \
	(ft_strlen(p->line) - p->j + ft_strlen(expanded)));
	if (!str)
		return (NULL);
	str = copy_with_value(str, expanded, *p, cursor);
	printf("len expanded :%zu\n", ft_strlen(expanded));
	p->i += ft_strlen(expanded) - p->j - 1;
	return (str);
}
