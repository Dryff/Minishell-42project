/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:41:06 by cgelin            #+#    #+#             */
/*   Updated: 2023/02/14 13:52:58 by colas            ###   ########.fr       */
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

char	*get_expanded(t_msh *msh, t_parse *p)
{
	// int count;
	char *arg;
	char *expanded;

	// count = 0;
	p->i++;
	p->j = p->i;
	while (p->line[p->j] && p->line[p->j] != '"' &&  p->line[p->j] != '\'' && p->line[p->j] != 10 \
	&& p->line[p->j] != ' ' && p->line[p->j] != '$')
		p->j++;
	arg = ft_substr(p->line, p->i, p->j - p->i);
	//printf("arg : %s\n", arg);
	expanded = ft_expand(&msh->env, arg);
	free(arg);
	p->j -= p->i;
	//printf("p.i :: %d\n", p->i);
	//printf("p.j :: %d\n", p->j);
	return (expanded);
}

char	*copy_with_value(char *str, char *expanded, t_parse p)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (++i < p.i - 1)
		str[i] = p.line[i];
	while (j < (int)ft_strlen(expanded))
		str[i++] = expanded[j++];
	// printf("(i : %d, strlen : %zu)\n", p.j, ft_strlen(p.line) + ft_strlen(expanded));
	while (i < (int)ft_strlen(p.line) + (int)ft_strlen(expanded) - p.j)
		str[i++] = p.line[p.i++ + p.j];
	str[i] = '\0';
	printf("|str : %s|\n", str);
	return (str);
}

int is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*replace_env_arg(t_msh *msh, t_parse *p)
{
	char	*expanded;
	char	*str;

	expanded = NULL;
	if (is_alpha(p->line[p->i + 1]))
		expanded = get_expanded(msh, p);
	else
	{
		expanded = "$";
		p->i++;
		p->j = 0;
	}
	// printf("expanded : %s\n", expanded);
	str = malloc(sizeof(char) * (ft_strlen(p->line) - p->j + ft_strlen(expanded)));
	if (!str)
		return (NULL);
	str = copy_with_value(str, expanded, *p);
	if (ft_strlen(expanded) - 1 > 0)
		p->i += ft_strlen(expanded) - 1;
	return (str);
}

char	*get_dollar(t_msh *msh, t_parse *p)
{
	p->i = p->s + 1;
	while (p->line[p->i] && p->line[p->i] != p->q)
	{
		if (p->line[p->i] == '$' && p->q == '"')
			p->line = replace_env_arg(msh, p);
		p->i++;
	}
	return (p->line);
}

char	*getline_rm_quote(t_parse p)
{
	char		*str;
	int			i;
	int			j;

	str = malloc(sizeof(char) * ft_strlen(p.line));
	i = 0;
	j = -1;
	if (!str)
		return (NULL);
	while (++j < p.s)
		str[j] = p.line[j];
	i = j;
	while (p.line[j] && j <= p.i)
	{
		if (p.line[j] != p.q)
			str[i++] = p.line[j];
		j++;
	}
	while (p.line[j])
		str[i++] = p.line[j++];
	return (str[i] = '\0', str);
}

int	is_end_of_arg(t_parse p)
{
	int	q_count;

	q_count = 0;
	if (!p.line[p.i + 1])
		return (1);
	if (p.line[p.i + 1] != ' ')
		return (0);
	while (p.i >= p.s)
	{
		if (p.line[p.i] == p.q)
			q_count++;
		p.i--;
	}
	if (q_count % 2 == 1)
		return (0);
	return (1);
}

int	quote_rm_nbr(t_parse p)
{
	int	count;

	count = 0;
	while (p.s <= p.i)
	{
		if (p.line[p.s] == p.q)
			count ++;
		p.s++;
	}
	return (count);
}

char	*replace_spaces(t_parse p)
{
	int	j;

	while (p.line[p.i] && !is_white_space(p.line[p.i]))
	{
		if (p.line[p.i] == '\'' || p.line[p.i] == '"')
			return (p.line);
		p.i++;
	}
	j = p.i;
	while (p.line[j] && p.line[j] != '\'' && p.line[j] != '"' \
	&& is_white_space(p.line[j]))
		j++;
	while (p.line[p.i] && p.i < j)
	{
		p.line[p.i] = 10;
		p.i++;
	}
	return (p.line);
}

int go_to_end_quote(t_parse p)
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
			printf("\n----\n%d\n----\n", p.s);
			p.line = get_dollar(&msh, &p);
			printf("\n----\n%d\n----\n", p.s);
			p.line = getline_rm_quote(p);
			p.i -= q_nbr;
		}
		else if (p.line[p.i] == '$')
			p.line = replace_env_arg(&msh, &p);
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
