/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arrays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:29:38 by colas             #+#    #+#             */
/*   Updated: 2023/04/17 14:34:20 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	get_count(char *str, char c)
{
	int		i;
	int		count;
	int		is_in_quotes;
	int		start_quote;

	is_in_quotes = 0;
	start_quote = 0;
	i = -1;
	count = 0;
	if (i <= (int)ft_strlen(str))
	{
		while (str[++i])
		{
			if (str[i] == c && !is_in_quotes)
			{
				while (str[i] == c)
					i++;
				count++;
			}
			quote_check(str, i, &start_quote, &is_in_quotes);
		}
	}
	if (is_in_quotes)
		return (-1);
	return (count);
}

t_outputs	*get_op_array(t_msh *msh, char *str, int cmd_id)
{
	t_outputs	*new;
	int			count;

	count = get_count(str, '>');
	if (count == -1)
		return (NULL);
	new = malloc((count + 1) * sizeof(t_outputs));
	if (!new)
		return (NULL);
	msh->cmd[cmd_id].redir_nbr = count;
	return (new);
}

char	**get_hd_array(t_msh *msh, char *str, int cmd_id)
{
	int		i;
	int		count;
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

char	**get_in_name_array(t_msh *msh, char *str, int cmd_id)
{
	char		**new;
	int			count;
	int			i;

	i = 0;
	count = get_count(str, '<');
	if (count == -1)
		return (NULL);
	new = malloc((count + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	msh->cmd[cmd_id].in_nbr = count;
	while (i <= count)
	{
		new[i] = NULL;
		i++;
	}
	return (new);
}