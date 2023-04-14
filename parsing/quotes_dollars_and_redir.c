/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_dollars_and_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:43:24 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/15 00:33:21 by cgelin           ###   ########.fr       */
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
	while (p.line[j] && j <= p.end_q)
	{
		if (p.line[j] != p.q)
			str[i++] = p.line[j];
		j++;
	}
	str[i] = '\0';
	while (p.line[j])
		str[i++] = p.line[j++];
	free(p.line);
	return (str[i] = '\0', str);
}

void	quote_handling(t_msh *msh, t_parse *p)
{	
	int	has_dollar;

	p->strt = p->i;
	has_dollar = 0;
	p->q = p->line[p->i];
	p->end_q = go_to_end_quote(*p, p->i, p->line);
	p->line = getline_rm_quote(msh, *p);
	p->end_q -= 2;
	if (p->q == '"')
		p->line = get_dollar(msh, p, &has_dollar);
	if (!has_dollar)
		p->i = p->end_q;
	secure(p);
}

void	init_output_input(t_msh *msh, char *str, int cmd_id)
{
	int	i;
	int	j;

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
	p.end_q = 0;
	init_output_input(msh, str, cmd_id);
	while (p.line[p.i])
	{
		if (p.line[p.i] == '"' || p.line[p.i] == '\'')
			quote_handling(msh, &p);
		else if (p.line[p.i] == '>' || p.line[p.i] == '<')
			get_redir(msh, &p, cmd_id);
		else if (p.line[p.i] == '$')
			p.line = replace_env_arg(msh, &p, &p.i, 0);
		else
			p.line = replace_spaces(p, p.line);
		if (p.line[p.i])
			p.i++;
	}
	return (p.line);
}
