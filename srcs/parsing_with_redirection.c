/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_with_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:59:29 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/02 16:28:15 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	parsing_with_redirection(char *arg, int *i, int *not_first_arg,
	int size)
{
	int	size_loc;

	size_loc = 0;
	if (size == 0)
	{
		while (check_char(arg[*i]) == 2)
		{
			*i += 1;
			size_loc++;
		}
		*not_first_arg = 1;
	}
	return (size_loc);
}

void	fill_cmd_redirection(char *arg, int *i, char *cmd, int *j)
{
	if (*j == 0)
	{
		while (check_char(arg[*i]) == 2)
		{
			cmd[*j] = arg[*i];
			*i += 1;
			*j += 1;
			if (!arg[*i])
			{
				*i = 0;
				return ;
			}
		}
	}
}
