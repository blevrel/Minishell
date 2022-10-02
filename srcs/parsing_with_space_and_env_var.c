/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_with_space_and_env_var.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:01:28 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/02 14:05:29 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	parsing_with_space(char *arg, int *i, int *not_first_arg, int *trigger)
{
	int	size;

	size = 0;
	if (check_char(arg[*i]) == 1)
	{
		*not_first_arg = 1;
		*trigger = 1;
	}
	if (!arg[*i + 1])
		return (reset_statics(i, not_first_arg, 0, 2));
	if (arg[*i] == '$')
	{
		(*i)++;
		if (*not_first_arg == 0)
			return (env_var_as_first_arg(arg, i, size));
		while (arg[*i] && check_char(arg[(*i)++]) == 0)
			size++;
		if (!arg[*i])
			return (reset_statics(i, not_first_arg, size + 1, 2));
		return (size + 1);
	}
	return (0);
}

int	env_var_as_first_arg(char *arg, int *i, int size)
{
	while (arg[*i] && (check_char(arg[*i]) == 0 || check_char(arg[*i]) == -1))
	{
		size++;
		(*i)++;
	}
	if (!arg[*i])
		return (reset_statics(i, NULL, size + 1, 1));
	if (check_char(arg[*i]) == 1)
		(*i)--;
	return (size + 1);
}

void	fill_cmd_space_and_env_var(char *arg, int *i, int *trigger, char *cmd)
{
	int			j;
	static int	not_first_arg = 0;

	j = 0;
	if (check_char(arg[*i]) == 1)
		not_first_arg = 1;
	if (not_first_arg == 1)
		*trigger = 1;
	if (arg[*i] != '$')
	{
		while (arg[*i] && (check_char(arg[*i]) == 0))
		{
			cmd[j] = arg[*i];
			(*i)++;
			j++;
		}
	}
	else
		fill_cmd_env_var(arg, i, cmd, not_first_arg);
	if (ft_strchr_int(&arg[*i], '$') == 0)
		not_first_arg = 0;
	if (next_non_spc_char(*i, arg) == ' ')
		*i = 0;
}

void	fill_cmd_env_var(char *arg, int *i, char *cmd, int not_first_arg)
{
	int	j;

	j = 0;
	if (!cmd[0])
	{
		if (not_first_arg == 0)
		{
			while (arg[*i] && check_char(arg[*i]) != 1)
			{
				cmd[j] = arg[*i];
				(*i)++;
				j++;
			}
			(*i)--;
			return ;
		}
		cmd[j] = arg[*i];
		(*i)++;
		while (arg[*i] && check_char(arg[*i]) == 0)
		{
			j++;
			cmd[j] = arg[*i];
			(*i)++;
		}
	}
}
