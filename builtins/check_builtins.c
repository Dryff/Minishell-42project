/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:53:30 by laquarium         #+#    #+#             */
/*   Updated: 2023/04/20 16:48:03 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	check_export(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (valid_export(str[i]) == WRONG_EXPORT)
		{
			ft_err_printf("msh: export: '%s': not a valid identifier\n"\
			, str[i]);
			update_msh_status(1);
			return (1);
		}
		i++;
	}
	update_msh_status(0);
	return (0);
}

int	check_exit(char **str)
{
	int		len;

	len = tab_len(str);
	if (len == 2)
	{
		if (!ft_str_is_numeric(str[1]))
			return (ft_err_printf("msh: exit: %s: numeric argument required\n"\
			, str[1]), 1);
	}
	if (len > 2)
	{
		if (!ft_str_is_numeric(str[1]))
			return (ft_err_printf("msh: exit: %s: numeric argument required\n"\
			, str[1]), 1);
		else
			return (ft_err_printf("msh: exit: too many arguments\n", 1));
	}
	return (0);
}
