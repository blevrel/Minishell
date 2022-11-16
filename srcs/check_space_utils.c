/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:50:44 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/15 17:16:26 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	space_before_redirection(char *first_occ)
{
	char	next_char;
	int		i;

	i = 0;
	if (!first_occ)
		return (0);
	while (check_char(&first_occ[i]) == 1)
		i++;
	while (check_char(&first_occ[i]) == 2)
		i++;
	i = move_to_end_of_arg(first_occ, i);
	next_char = next_non_spc_char(i, first_occ);
	if (next_char && check_char(&next_char) <= 0)
		return (1);
	return (0);
}

int	check_if_space_is_needed(char *cmd, char *first_occ)
{
	int		cmd_size;
	char	next_char;

	cmd_size = ft_strlen(cmd);
	next_char = next_non_spc_char(cmd_size, first_occ);
	if (check_char(&first_occ[cmd_size]) < 0)
	{
		cmd_size = move_to_end_of_arg(first_occ, cmd_size);
		if (check_char(&first_occ[cmd_size]) == 1)
			return (1);
	}
	if (check_char(&first_occ[cmd_size]) == 1 && check_char(&next_char) <= 0)
		return (1);
	if (check_char(&first_occ[cmd_size]) == 1 && check_char(&next_char) == 2)
	{
		if (space_before_redirection(&first_occ[cmd_size]) == 1)
			return (1);
	}
	return (0);
}

void	space_before_first_arg(char *full_arg, int arg_i)
{
	while (check_char(&full_arg[arg_i]) == 1)
		arg_i++;
	while (check_char(&full_arg[arg_i]) != 1)
		arg_i++;
	while ((check_char(&full_arg[arg_i]) == 1)
		|| (check_char(&full_arg[arg_i]) < 0
			&& full_arg[arg_i] == full_arg[arg_i + 1]))
	{
		if (check_char(&full_arg[arg_i]) < 0
			&& full_arg[arg_i] == full_arg[arg_i + 1])
		{
			arg_i += 2;
			if (check_char(&full_arg[arg_i]) == 1)
				ft_printf(" ");
		}
		else
			arg_i++;
	}
}


