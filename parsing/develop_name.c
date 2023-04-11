/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   develop_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:40:05 by colas             #+#    #+#             */
/*   Updated: 2023/04/10 19:25:50 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*develop_name(t_msh *msh, char *sub)
{
	t_parse	p;

	p.line = sub;
	p.i = 0;
	p.strt = 0;
	if (p.line == NULL)
		return (NULL);
	while (p.line[p.i])
	{
		if (p.line[p.i] == '"' || p.line[p.i] == '\'')
		{
			p.strt = p.i;
			quote_handling(msh, &p);
		}
		else if (p.line[p.i] == '$')
			p.line = replace_env_arg(msh, &p, p.i);
		if (p.line[p.i])
			p.i++;
	}
	return (p.line);
}
