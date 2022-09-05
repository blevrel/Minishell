/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_with_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:55:54 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/03 14:52:24 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	cmd_tab_size_quotes(int *i, char *arg, int c)
{
	int	quote;

	quote = 0;
	if (!arg[*i + 1])
		return ;
	*i += 1;
	while (arg[*i])
	{
		if (arg[*i] == c)
			quote = 1;
		if ((arg[*i] == c && check_char(arg[*i + 1]) != 0)
			|| (check_char(arg[*i]) == 1 && quote == 1)
			|| (check_char(arg[*i]) == 2 && quote == 1))
			break ;
		*i += 1;
	}
	return ;
}

int	reset_statics(int *i, int *trigger, int size)
{
	*i = 0;
	*trigger = 0;
	return (size);
}

int	parsing_with_quotes(char *arg, int *i, int *not_first_arg, int c)
{
	int	size;
	int	quote;

	quote = 0;
	size = 1;
	*i += 1;
	if (*not_first_arg == 0)
		return (parsing_with_quotes_first_arg(arg, i, size, not_first_arg));
	while (arg[*i])
	{
		if (arg[*i] == c)
			quote = 1;
		if (!arg[*i + 1])
			return (reset_statics(i, not_first_arg, size + 1));
		if ((arg[*i] == c && check_char(arg[*i + 1]) > 0)
			|| (check_char(arg[*i]) == 1 && quote == 1)
			|| (check_char(arg[*i]) == 2 && quote == 1))
			break ;
		*i += 1;
		size++;
	}
	*i += 1;
	size++;
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
			return (reset_statics(i, not_first_arg, size));
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
	cmd[j] = arg[*i];
	*i += 1;
	while (arg[*i])
	{
		j++;
		if (arg[*i] == c)
			quote = 1;
		if ((arg[*i] == c || quote == 1) && check_char(arg[*i + 1]) > 0)
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
		*i += 1;
	}
}
