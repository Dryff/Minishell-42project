/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emoji.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:23:26 by mfinette          #+#    #+#             */
/*   Updated: 2023/04/13 16:05:13 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	get_value(char *str)
{
	int	value;

	value = 0;
	while (*str)
	{
		value += *str;
		str++;
	}
	return (value);
}

char	*select_good_prompt(t_msh *msh)
{
	int	value;
	(void)msh;
	
	value = 0;
	// printf("value = %d\n", value);
	return (select_good_prompt_1(value));
}

char	*select_good_prompt_1(int value)
{
	static int	i = 0;

	i++;
	i += value;
	if (i % 20 == 0)
		return (GOOD_PROMPT_1);
	else if (i % 20 == 1)
		return (GOOD_PROMPT_2);
	else if (i % 20 == 2)
		return (GOOD_PROMPT_3);
	else if (i % 20 == 3)
		return (GOOD_PROMPT_4);
	else if (i % 20 == 4)
		return (GOOD_PROMPT_5);
	else if (i % 20 == 5)
		return (GOOD_PROMPT_6);
	else if (i % 20 == 6)
		return (GOOD_PROMPT_7);
	else if (i % 20 == 7)
		return (GOOD_PROMPT_8);
	else if (i % 20 == 8)
		return (GOOD_PROMPT_9);
	else if (i % 20 == 9)
		return (GOOD_PROMPT_10);
	return (select_good_prompt_2(i));
}

char	*select_good_prompt_2(int value)
{
	// static int	i;
	int	i;
	i = value;
	// i++;
	if (i % 20 == 0)
		return (GOOD_PROMPT_11);
	else if (i % 20 == 1)
		return (GOOD_PROMPT_12);
	else if (i % 20 == 2)
		return (GOOD_PROMPT_13);
	else if (i % 20 == 3)
		return (GOOD_PROMPT_14);
	else if (i % 20 == 4)
		return (GOOD_PROMPT_15);
	else if (i % 20 == 5)
		return (GOOD_PROMPT_16);
	else if (i % 20 == 6)
		return (GOOD_PROMPT_17);
	else if (i % 20 == 7)
		return (GOOD_PROMPT_18);
	else if (i % 20 == 8)
		return (GOOD_PROMPT_19);
	else if (i % 20 == 9)
		return (GOOD_PROMPT_20);
	return (select_good_prompt_1(i));
}

char	*select_bad_prompt_1(void)
{
	static int	i = 0;

	i++;
	if (i % 20 == 0)
		return (BAD_PROMPT_1);
	else if (i % 20 == 1)
		return (BAD_PROMPT_2);
	else if (i % 20 == 2)
		return (BAD_PROMPT_3);
	else if (i % 20 == 3)
		return (BAD_PROMPT_4);
	else if (i % 20 == 4)
		return (BAD_PROMPT_5);
	else if (i % 20 == 5)
		return (BAD_PROMPT_6);
	else if (i % 20 == 6)
		return (BAD_PROMPT_7);
	else if (i % 20 == 7)
		return (BAD_PROMPT_8);
	else if (i % 20 == 8)
		return (BAD_PROMPT_9);
	else if (i % 20 == 9)
		return (BAD_PROMPT_10);
	return (select_bad_prompt_2());
}

char	*select_bad_prompt_2(void)
{
	static int	i = 0;

	i++;
	if (i % 20 == 0)
		return (BAD_PROMPT_11);
	else if (i % 20 == 1)
		return (BAD_PROMPT_12);
	else if (i % 20 == 2)
		return (BAD_PROMPT_13);
	else if (i % 20 == 3)
		return (BAD_PROMPT_14);
	else if (i % 20 == 4)
		return (BAD_PROMPT_15);
	else if (i % 20 == 5)
		return (BAD_PROMPT_16);
	else if (i % 20 == 6)
		return (BAD_PROMPT_17);
	else if (i % 20 == 7)
		return (BAD_PROMPT_18);
	else if (i % 20 == 8)
		return (BAD_PROMPT_19);
	else if (i % 20 == 9)
		return (BAD_PROMPT_20);
	else
		return (select_bad_prompt_1());
}
