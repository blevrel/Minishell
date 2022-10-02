/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_with_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:55:54 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/02 14:02:23 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	cmd_tab_size_quotes(int *i, char *arg, int c)
{
	int	quote;

	quote = 0;
	if (!arg[*i + 1])
		return ;
	(*i)++;
	while (arg[*i])
	{
		if (arg[*i] == c)
			quote = 1;
		if (arg[*i] == c && arg[*i - 1] == c && arg[*i - 2] == c)
		{
			quote = 0;
			(*i)++;
			continue ;
		}
		if ((arg[*i] == c && check_char(arg[*i + 1]) != 0 && quote != 1)
			|| (check_char(arg[*i]) == 1 && quote == 1)
			|| (check_char(arg[*i]) == 2 && quote == 1)
			|| (check_char(arg[*i]) == -1 && quote == 1))
			break ;
		(*i)++;
	}
	if (arg[*i])
		(*i)--;
	return ;
}

int	reset_statics(int *i, int *j, int size, int trigger)
{
	if (trigger == 2)
	{
		*i = 0;
		*j = 0;
	}
	else if (trigger == 1)
		*i = 0;
	else if (trigger == 0)
		*j = *i;
	return (size);
}

int	parsing_with_quotes(char *arg, int *i, int *not_first_arg, int c)
{
	int	size;
	int	quote;

	quote = 0;
	size = 1;
	(*i)++;
	if (*not_first_arg == 0)
		return (parsing_with_quotes_first_arg(arg, i, size, not_first_arg));
	while (arg[*i])
	{
		if (!arg[*i + 1])
			return (reset_statics(i, not_first_arg, size + 1, 2));
		if (arg[*i] == c)
			quote = 1;
		if ((arg[*i] == c && arg[*i - 1] == c && arg[*i - 2] == c)
			|| (quote == 1 && check_closing_quotes(&arg[*i]) == 0))
		{
			quote = 0;
			(*i)++;
			continue ;
		}
		if ((arg[*i] == c && check_char(arg[*i + 1]) > 0)
			|| (quote == 1 && (check_char(arg[*i]) == 1 || check_char(arg[*i])
					== 2 || check_char(arg[*i]) == -1)))
			break ;
		(*i)++;
		size++;
	}
	if (arg[*i])
	{
		(*i)++;
		size++;
	}
	*not_first_arg = 1;
	return (size);
}

int	parsing_with_quotes_first_arg(char *arg, int *i, int size,
		int *not_first_arg)
{
	while (check_char(arg[*i]) != 1 && check_char(arg[*i]) != 2 && arg[*i])
	{
		size++;
		*i += 1;
		if (!arg[*i + 1])
			return (reset_statics(i, not_first_arg, size, 2));
	}
	*not_first_arg = 1;
	return (size);
}

void	fill_cmd_quotes(char *arg, int *i, char *cmd, int c)
{
	int	j;
	int	quote;

	quote = 0;
	j = 0;
	cmd[j] = arg[(*i)++];
	while (arg[*i])
	{
		j++;
		if (arg[*i] == c)
			quote = 1;
		if ((arg[*i] == c && arg[*i - 1] == c && arg[*i - 2] == c)
			|| (quote == 1 && check_closing_quotes(&arg[*i]) == 0))
		{
			quote = 0;
			cmd[j] = arg[*i];
			(*i)++;
			continue ;
		}
		if ((quote == 1 && check_char(arg[*i + 1]) > 0)
			|| (quote == 1 && check_char(arg[*i + 1]) == -1))
		{
			cmd[j] = arg[(*i)++];
			return ;
		}
		cmd[j] = arg[*i];
		if (!arg[*i + 1])
		{
			*i = 0;
			return ;
		}
		(*i)++;
	}
}
