/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_with_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:55:54 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/24 17:16:44 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	cmd_tab_size_quotes(int *i, char *arg)
{
	int	count;

	count = 0;
	if (check_char(arg[*i - 1]) == 0)
		count++;
	*i += 1;
	while (check_char(arg[*i]) != -1)
	{
		if (!arg[*i + 1])
			break ;
		*i += 1;
	}
	if (check_char(arg[*i + 1]) <= 0 && arg[*i + 1])
		count++;
	return (count);
}

int	allocate_cmd_with_quotes(int *i, char *arg, int *trigger)
{
	int	size;

	size = 0;
	*i += 1;
	size++;
	while (check_char(arg[*i]) != -1)
	{
		if (!arg[*i + 1])
			*i = -1;
		size++;
		*i += 1;
	}
	*trigger = 1;
	size++;
	return (size);
}

void	fill_cmd_tab_with_quotes(int *i, char *arg, char *cmd)
{
	int	j;

	j = 0;
	cmd[j] = arg[*i];
	*i += 1;
	j++;
	while (check_char(arg[*i]) != -1)
	{
		cmd[j] = arg[*i];
		*i += 1;
		j++;
	}
	cmd[j] = arg[*i];
}
