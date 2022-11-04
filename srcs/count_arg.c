/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:32:51 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/04 15:39:36 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	go_to_first_arg(char *arg, int *i)
{
	int	count;
	int	quote;

	count = 0;
	while (check_char(&arg[*i]) == 2)
	{
		(*i)++;
		if (check_char(&arg[*i]) != 2)
			return (1);
	}
	while (arg[*i] && (check_char(&arg[*i]) <= 0))
	{	
		if (check_char(&arg[*i]) < 0)
		{
			quote = arg[(*i)++];
			while (arg[*i] && arg[*i] != quote)
					(*i)++;
		}
		count++;
		if (arg[*i])
			(*i)++;
	}
	if (arg[*i] && check_char(&arg[*i]) == 0)
		return (0);
	return (1);
}

int	count_arg(char *arg, int *i)
{
	int	res;

	res = 0;
	while (arg[*i] && arg[*i] != '|')
	{
		while (arg[*i] && check_char(&arg[*i]) == 1)
			(*i)++;
		if (arg[*i] && check_char(&arg[*i]) == 2)
		{
			if (check_here_doc_null(&arg[*i]) == 1)
				res++;
			res++;
		}
		while (check_char(&arg[*i]) == 2)
				(*i)++;
		if (arg[*i] && check_char(&arg[*i]) == 0 && arg[*i] != '|')
		{
			while (arg[*i] && check_char(&arg[*i]) == 0)
				(*i)++;
			res++;
		}
		res += check_quote(arg, i);
	}
	return (res);
}

int	skip_space(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && check_char(&arg[i]) == 1)
			i++;
	return (i);
}

int	nb_arg(char *arg)
{
	int	i;
	int	res;
	int	check_exp;

	res = 0;
	i = 0;
	check_exp = 0;
	while (arg[i])
	{
		i += skip_space(&arg[i]);
		check_exp = check_export(&arg[i]);
		res += go_to_first_arg(arg, &i);
		i += skip_space(&arg[i]);
		if (arg[i] == '|')
		{
			while (arg[i] == '|')
				i++;
			res++;
		}
		if (check_exp == 1)
			res += count_exp(arg, &i);
		if (res != 0 && arg[i])
			res += count_arg(arg, &i);
	}
	return (res);
}
