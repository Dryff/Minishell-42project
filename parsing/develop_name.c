/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   develop_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:40:05 by colas             #+#    #+#             */
/*   Updated: 2023/04/17 17:05:42 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*develop_name(t_msh *msh, char *sub, int hd)
{
	t_parse	p;

	p.line = sub;
	p.i = 0;
	p.strt = 0;
	p.end_q = 0;
	if (p.line == NULL)
		return (NULL);
	while (p.line[p.i])
	{
		if (p.line[p.i] == '"' || p.line[p.i] == '\'')
		{
			p.strt = p.i;
			quote_handling(msh, &p);
		}
		else if (p.line[p.i] == '$' && !hd)
			p.line = replace_env_arg(msh, &p, &p.i, 0);
		if (p.i < (int)ft_strlen(p.line))
			p.i++;
	}
	return (p.line);
}

void	handle_here_doc(t_msh *msh, char *sub, int cmd_ind)
{
	msh->cmd[cmd_ind].ip.need_develop = 1;
	if (msh->cmd[cmd_ind].hd_id == msh->cmd[cmd_ind].hd_nbr - 1 \
	&& ft_strchr(sub, '\''))
		msh->cmd[cmd_ind].ip.need_develop = 0;
	msh->cmd[cmd_ind].ip.here_doc_delim[msh->cmd[cmd_ind].hd_id] \
	= develop_name(msh, sub, 1);
	msh->cmd[cmd_ind].hd_id++;
}
