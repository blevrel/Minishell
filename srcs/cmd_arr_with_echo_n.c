/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr_with_echo_n.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 04:26:01 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/18 20:09:15 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	only_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	check_option_syntax(char **cmd, int cmd_i, int i)
{
	while (cmd[cmd_i][i])
	{
		if (cmd[cmd_i][i] == '-')
			i++;
		else
			return (1);
		while (cmd[cmd_i][i] == 'n')
			i++;
		if (cmd[cmd_i][i] == '-')
			return (1);
	}
	return (0);
}

int	is_valid_option(char **cmd, int cmd_i)
{
	int	i;

	i = 0;
	if (only_n(cmd[cmd_i]) == 0)
	{
		if (ft_strcmp(cmd[cmd_i - 1], "-") == 0
			|| is_valid_option(cmd, cmd_i - 1) == 0)
			return (0);
	}
	if (ft_strcmp(cmd[cmd_i], "-") == 0)
	{
		if (only_n(cmd[cmd_i + 1]) == 1)
			return (1);
	}
	if (check_option_syntax(cmd, cmd_i, i) == 1)
		return (1);
	return (0);
}

int	move_cmd_arr_index(char **cmd, char *options)
{
	int	cmd_i;
	int	cmd_j;
	int	i;

	cmd_i = 1;
	cmd_j = 0;
	i = 0;
	while (options[i])
	{
		while (options[i] && options[i] == cmd[cmd_i][cmd_j])
		{
			i++;
			cmd_j++;
		}
		if (!cmd[cmd_i][cmd_j] && is_valid_option(cmd, cmd_i + 1) == 1)
			return (cmd_i + 1);
		cmd_i++;
		cmd_j = 0;
	}
	return (cmd_i);
}
