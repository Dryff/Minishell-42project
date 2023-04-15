/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 22:34:33 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/15 01:48:39 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*get_expanded(t_msh *msh, t_parse *p, int cursor)
{
	char	*arg;
	char	*expanded;
	int		k;

	k = cursor;
	while (p->line[k] && (is_num(p->line[k]) || is_alpha(p->line[k])))
		k++;
	arg = ft_substr(p->line, cursor, k - cursor);
	expanded = ft_expand(&msh->env, arg);
	free(arg);
	k -= cursor;
	p->arg_sz = k;
	return (expanded);
}

void	actualize_ind(t_parse *p, char *expanded, char *str, int is_in_q)
{
	if (is_in_q)
	{
		p->i = p->end_q + (ft_strlen(expanded) - p->arg_sz - 1);
		p->end_q = p->i;
	}
	else if (ft_strlen(expanded))
		p->i += ft_strlen(expanded) - 1;
	else
		p->i--;
	if (p->arg_sz)
	{		
		if (p->i < 0)
			p->i = 0;
		else if (p->i > (int)ft_strlen(str))
			p->i = ft_strlen(str);
	}
}

void	secure(t_parse *p)
{
	if (p->i <= 0)
		p->i = 0;
	if (p->i > (int)ft_strlen(p->line))
		p->i = (int)ft_strlen(p->line);
}
