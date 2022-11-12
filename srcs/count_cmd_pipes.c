/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmd_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:13:21 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/12 14:34:07 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_nbpipe(char *full_arg)
{
	int	res;
	int	i;
	int	quote;

	i = 0;
	res = 1;
	while (full_arg[i])
	{
		if (check_char(&full_arg[i]) < 0)
		{
			quote = full_arg[i];
			i++;
			while (full_arg[i] != quote)
				i++;
			i++;
		}
		if (full_arg[i] == '|')
			res++;
		if (full_arg[i] && check_char(&full_arg[i]) >= 0)
			i++;
	}
	return (res);
}

int	count_quotes_and_pipes(char *full_arg, int *i, int res, int *nb_pipe)
{
	int	inside;

	inside = 1;
	if (*i == 0)
		res++;
	if (*i != 0 && check_char(&full_arg[*i]) < 0
		&& check_char(&full_arg[*i - 1]) != 0)
		res++;
	while (full_arg[*i] && check_char(&full_arg[*i]) < 1)
	{
		if (check_char(&full_arg[*i]) < 0)
			*i = move_index_after_quote(full_arg, *i);
		else
			(*i)++;
	}
	if (full_arg[*i] == '|')
	{
		(*i)++;
		res++;
		(*nb_pipe)++;
	}
	return (res);
}

int	nb_cmd(char *full_arg, int index_pipe)
{
	int	i;
	int	res;
	int	nb_pipe;

	i = 0;
	res = 0;
	nb_pipe = 0;
	while (full_arg[i] && nb_pipe < index_pipe)
	{
		while (full_arg[i] && check_char(&full_arg[i]) == 1)
			i++;
		if (full_arg[i] && check_char(&full_arg[i]) == 2)
			res++;
		while (check_char(&full_arg[i]) == 2)
				i++;
		if (full_arg[i] && check_char(&full_arg[i]) == 0)
			res++;
		while (full_arg[i] && check_char(&full_arg[i]) == 0)
			i++;
		res = count_quotes_and_pipes(full_arg, &i, res, &nb_pipe);
	}
	return (res);
}
