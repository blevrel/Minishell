/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:32:51 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/10 10:35:12 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	go_to_first_arg(char *arg, int *i)
{
	int	count;
	int	quote;

	count = 0;
	while (arg[*i] && check_char(&arg[*i]) == 1)
		(*i)++;
	while (arg[*i] && check_char(&arg[*i]) <= 0)
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
	if (count <= 0)
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
			res++;
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

int	nb_arg(char *arg)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (arg[i])
	{
		res += go_to_first_arg(arg, &i);
		while (arg[i] && check_char(&arg[i]) == 1)
			i++;
		if (arg[i] == '|')
		{
			while (arg[i] == '|')
				i++;
			res++;
		}
		if (res != 0 && arg[i])
			res += count_arg(arg, &i);
	}
	return (res);
}

int	count_size_first_arg(char *arg)
{
	int	i;
	int	res;
	int	quote;

	i = 0;
	res = 0;
	quote = 0;
	while (arg[i] && check_char(&arg[i]) == 1)
		i++;
	while (arg[i] && check_char(&arg[i]) <= 0)
	{
		if (check_char(&arg[i]) < 0)
		{
			quote = arg[i];
			while (arg[++i] != quote)
				res++;
		}
		i++;
		res++;
	}
	return (res);
}

int	count_size_arg(char *arg, int value)
{
	int	i;

	i = 0;
	while (arg[i] && check_char(&arg[i]) == value)
		i++;
	return (i);
}
