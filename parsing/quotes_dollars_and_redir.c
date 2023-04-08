/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_dollars_and_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:24 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/05 14:58:28 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*getline_rm_quote(t_msh *msh, t_parse p)
{
	char		*str;
	int			i;
	int			j;

	str = malloc(sizeof(char) * ft_strlen(p.line) + 1);
	if (!str)
		return (error_manager(msh, MALLOC_ERR), NULL);
	i = 0;
	j = -1;
	while (++j < p.strt)
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
	free(p.line);
	return (str[i] = '\0', str);
}

int	quote_rm_nbr(t_parse p)
{
	int	count;

	count = 0;
	while (p.strt <= p.i)
	{
		if (p.line[p.strt] == p.q)
			count ++;
		p.strt++;
	}
	return (count);
}

void	quote_handling(t_msh *msh, t_parse *p)
{	
	int	q_nbr;

	p->q = p->line[p->i];
	p->i = go_to_end_quote(p->i, p->line, p->q, p->strt);
	q_nbr = quote_rm_nbr(*p);
	p->line = get_dollar(msh, p);
	p->line = getline_rm_quote(msh, *p);
	p->i -= q_nbr;
	if (p->i <= 0)
		p->i = 0;
	if (p->i >= (int)ft_strlen(p->line))
		p->i = (int)ft_strlen(p->line);
}

t_outputs	*get_op_array(t_msh *msh, char *str, int cmd_id)
{
	int 	i;
	int 	count;
	int		is_in_quotes;
	int		start_quote;
	t_outputs	*new;

	is_in_quotes = 0;
	start_quote = 0;
	i = -1;
	count = 0;
	if (i <= (int)ft_strlen(str))
	{
		while (str[++i])
		{
			if (str[i] == '>' && !is_in_quotes)
			{
				while (str[i] == '>')
					i++;
				count++;
			}
			quote_check(str, i, &start_quote, &is_in_quotes);
		}
	}
	if (is_in_quotes)
		return (NULL);
	new = malloc((count + 1) * sizeof(t_outputs));
	if (!new)
		return (NULL);
	msh->cmd[cmd_id].redir_nbr = count;
	return (new);
}

char	**get_hd_array(t_msh *msh, char *str, int cmd_id)
{
	int 	i;
	int 	count;
	int		is_in_quotes;
	int		start_quote;
	char	**new;

	is_in_quotes = 0;
	start_quote = 0;
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && !is_in_quotes)
		{
			while (str[i] == '<')
				i++;
			count++;
		}
		quote_check(str, i, &start_quote, &is_in_quotes);
	}
	new = malloc((count + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	msh->cmd[cmd_id].hd_nbr = count;
	return (new);
}

void	init_output_input(t_msh *msh, char *str, int cmd_id)
{
	int i;
	int j;

	j = 0;
	i = 0;
	msh->cmd[cmd_id].op = get_op_array(msh, str, cmd_id);
	while (j < msh->cmd[cmd_id].redir_nbr)
	{
		msh->cmd[cmd_id].op[j].output = 0;
		msh->cmd[cmd_id].op[j].outfd = 0;
		msh->cmd[cmd_id].op[j].out_name = NULL;
		j++;
	}
	j = -1;
	msh->cmd[cmd_id].ip.here_doc_delim = get_hd_array(msh, str, cmd_id);
	while (++j < msh->cmd[cmd_id].hd_nbr)
		msh->cmd[cmd_id].ip.here_doc_delim[0] = NULL;
	msh->cmd[cmd_id].ip.input = 0;
	msh->cmd[cmd_id].ip.infd = 0;
	msh->cmd[cmd_id].ip.in_name = NULL;
	msh->redir_id = 0;
	msh->cmd[cmd_id].hd_id = 0;
	i++;
}	

char	*quotes_dollars_and_redir(t_msh *msh, char *str, int cmd_id)
{
	t_parse	p;

	p.line = str;
	p.i = 0;
	p.strt = 0;
	init_output_input(msh, str, cmd_id);
	while (p.line[p.i])
	{
		if (p.line[p.i] == '"' || p.line[p.i] == '\'')
		{
			p.strt = p.i;
			quote_handling(msh, &p);
			p.line = replace_spaces(p, p.line);
		}
		else if (p.line[p.i] == '>' || p.line[p.i] == '<')
			get_redir(msh, &p, cmd_id);
		else if (p.line[p.i] == '$')
			p.line = replace_env_arg(msh, &p, p.i);
		else
			p.line = replace_spaces(p, p.line);
		if (p.line[p.i])
			p.i++;
	}
	return (p.line);
}
