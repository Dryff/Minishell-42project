/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/20 02:09:31 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	go_to_end_quote(int i, char *line, char q, int s)
{
	while (line[i] && !is_end_of_arg(i, line, q, s))
		i++;
	while (line[i] && line[i] != q)
		i--;
	return (i);
}

void	quote_handling(t_msh *msh, t_parse *p)
{
	int	q_nbr;

	p->q = p->line[p->i];
	p->s = p->i;
	p->i = go_to_end_quote(p->i, p->line, p->q, p->s);
	q_nbr = quote_rm_nbr(*p);
	printf("p->iavant = %d\n", p->i);
	p->line = get_dollar(msh, p);
	printf("p->iapres = %d\n", p->i);
	printf("p->line = %s\n", p->line);
	p->line = getline_rm_quote(*p);
	p->i -= q_nbr;
	printf("if q : %d\n", p->i);
}

char	*rm_quotes(t_msh msh, char *sub)
{
	t_parse	p;

	p.line = sub;
	p.i = -1;
	while (p.line[++p.i])
	{
		p.q = 0;
		printf("\n----TOUR----\n");
		printf("p->line = %s\n", p.line);
		if (p.line[p.i] == '"' || p.line[p.i] == '\'')
			quote_handling(&msh, &p);
		else if (p.line[p.i] == '$')
			p.line = replace_env_arg(&msh, &p, p.i);
		p.line = replace_spaces(p);
	}
	return (p.line);
}

void	store_cmd(t_msh *msh, int i, int j)
{
	char	*cmd;
	char	*sub;

	sub = ft_substr(msh->line, i, get_size(msh->line, i));
	cmd = rm_quotes(*msh, sub);
	msh->cmd[j].param = ft_split(cmd, 10);
}

int	parse_line(t_msh *msh)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	msh->cmd_nbr = get_cmd_nbr(msh->line);
	msh->cmd = malloc(sizeof(t_cmd) * msh->cmd_nbr);
	if (!msh->cmd)
		return (0);
	while (msh->line[i])
	{
		while (msh->line[i] && (msh->line[i] == '|' \
					|| is_white_space(msh->line[i])))
			i++;
		i = go_after_fd_name(msh, i);
		if (msh->line[i])
			store_cmd(msh, i, j++);
		while (msh->line[i] && !is_delimiter(msh->line[i]))
			i++;
	}
	return (1);
}
