/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:24 by mfinette          #+#    #+#             */
/*   Updated: 2023/02/19 14:41:38 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_cmd_nbr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_white_space(str[i]))
			count = 1;
		i++;
	}
	i = 0;
	while (str[i])
	{	
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	*get_expanded(t_msh *msh, t_parse *p, int cursor)
{
	char	*arg;
	char	*expanded;
	// int count;

	// count = 0;
	p->j = cursor;
	while (p->line[p->j] && p->line[p->j] != '"' && p->line[p->j] != '\'' && p->line[p->j] != 10 \
			&& p->line[p->j] != ' ' && p->line[p->j] != '$')
		p->j++;
	arg = ft_substr(p->line, cursor, p->j - cursor);
	printf("arg : %s\n", arg);
	expanded = ft_expand(&msh->env, arg);
	free(arg);
	p->j -= cursor;
	//printf("p.i :: %d\n", p->i);
	//printf("p.j :: %d\n", p->j);
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
	// printf("(i : %d, strlen : %zu)\n", p.j, ft_strlen(p.line) + ft_strlen(expanded));
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
		p->j = 0;
	}
	printf("expanded : %s\n", expanded);
	str = malloc(sizeof(char) * (ft_strlen(p->line) - p->j + ft_strlen(expanded)));
	if (!str)
		return (NULL);
	str = copy_with_value(str, expanded, *p, cursor);
	if (ft_strlen(expanded) - 1 > 0)
		p->i += ft_strlen(expanded) - 1;
	return (str);
}
