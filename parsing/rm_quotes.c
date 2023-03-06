/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:24 by mfinette          #+#    #+#             */
/*   Updated: 2023/03/03 18:02:42 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	go_to_end_quote(int i, char *line, char q, int s)
{
	while (line[i] && !is_end_of_arg(i, line, q, s))
		i++;
	while (i > 0 && line[i] != q)
		i--;
	return (i);
}

int	go_to_end_of_arg(int i, char *line, char q, int s)
{
	while (line[i] && !is_end_of_arg(i, line, q, s))
		i++;
	return (i);
}

void	quote_handling(t_msh *msh, t_parse *p, int *q_nbr)
{
	p->i = go_to_end_of_arg(p->i, p->line, p->q, p->strt);
	*q_nbr = quote_rm_nbr(*p);
	p->line = get_dollar(msh, p);
	p->line = getline_rm_quote(*p);
}

char	*rm_quotes(t_msh msh, char *sub)
{
	t_parse	p;
	int	q_nbr;

	p.line = sub;
	p.i = 0;
	while (p.line[p.i])
	{
		p.q = 0;
		if (p.line[p.i] == '"' || p.line[p.i] == '\'')
		{
			p.q = p.line[p.i];
			p.strt = p.i;
			quote_handling(&msh, &p, &q_nbr);
			p.i -= q_nbr;
		}
		else if (p.line[p.i] == '$')
			p.line = replace_env_arg(&msh, &p, p.i);
		p.line = replace_spaces(p);
		p.i++;
	}
	printf("p.line = %s\n", p.line);
	return (p.line);
}
