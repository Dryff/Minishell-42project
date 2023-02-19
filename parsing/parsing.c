/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/19 14:36:51 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	go_to_end_quote(t_parse p)
{
	while (p.line[p.i] && !is_end_of_arg(p))
		p.i++;
	while (p.line[p.i] && p.line[p.i] != p.q)
		p.i--;
	return (p.i);
}

char	*rm_quotes(t_msh msh, char *sub)
{
	int		q_nbr;
	t_parse	p;

	p.line = sub;
	p.i = -1;
	while (p.line[++p.i])
	{
		if (p.line[p.i] == '"' || p.line[p.i] == '\'')
		{
			p.q = p.line[p.i];
			p.s = p.i;
			p.i = go_to_end_quote(p);
			q_nbr = quote_rm_nbr(p);
			p.line = get_dollar(&msh, &p);
			p.line = getline_rm_quote(p);
			p.i -= q_nbr;
			printf("if q : %d\n", p.i);
		}
		else if (p.line[p.i] == '$')
		{
			p.line = replace_env_arg(&msh, &p, p.i);
			printf("if noq : %d\n", p.i);
		}
		p.line = replace_spaces(p);
	}
	return (p.line);
}

int	go_after_fd_name(t_msh *msh, int i)
{
	if (msh->line[i] == '>' || msh->line[i] == '<')
	{
		while (msh->line[i] && is_delimiter(msh->line[i]))
			i++;
		while (msh->line[i] && (is_white_space(msh->line[i]) \
					|| is_delimiter(msh->line[i])))
			i++;
		while (msh->line[i] && !is_white_space(msh->line[i]) \
				&& !is_delimiter(msh->line[i]))
			i++;
	}
	return (i);
}

int	parse_line(t_msh *msh)
{
	int		i;
	int		j;
	char	*cmd;
	char	*sub;

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
		{
			sub = ft_substr(msh->line, i, get_size(msh->line, i));
			cmd = rm_quotes(*msh, sub);
			msh->cmd[j++].param = ft_split(cmd, 10);
		}
		while (msh->line[i] && !is_delimiter(msh->line[i]))
			i++;
	}
	j = 0;
	printf("cmd_nbr : %d\n-----\n", msh->cmd_nbr);
	while (j < msh->cmd_nbr)
	{
		i = 0;
		printf("cmd : %d\n", j);
		while (msh->cmd[j].param[i])
		{
			printf("param [%d]: %s\n", i, msh->cmd[j].param[i]);
			i++;
		}
		j++;
		printf("---------\n");
	}
	return (1);
}
