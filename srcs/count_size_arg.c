/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_size_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:29:47 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/03 16:51:21 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_size_quote(char *arg, int *i)
{
	int	quote;
	int	res;

	res = 0;
	quote = arg[*i];
	(*i)++;
	res++;
	while (arg[*i] != quote)
	{
		res++;
		(*i)++;
	}
	return (res);
}

int	count_size_first_arg(char *arg)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (arg[i] && check_char(&arg[i]) == 1)
		i++;
	while (arg[i] && (check_char(&arg[i]) == 2))
	{
		++i;
		++res;
	}
	while (arg[i] && check_char(&arg[i]) <= 0)
	{
		if (check_char(&arg[i]) < 0)
			res += count_size_quote(&arg[i], &i);
		i++;
		res++;
	}
	return (res);
}

int	count_size_arg(char *arg, int value, int *i)
{
	int	count;

	count = 0;
	if (value == 2)
		while (arg[*i] && check_char(&arg[*i]) == value)
		{
			(*i)++;
			count++;
		}
	else
		while (arg[*i] && check_char(&arg[*i]) <= 0)
		{
			if (check_char(&arg[*i]) < 0)
				count += alloc_with_quotes(arg, i);
			else
			{
				(*i)++;
				count++;
			}
		}
	return (count);
}
