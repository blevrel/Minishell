/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:53 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 04:14:21 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_if_space_is_needed(char *cmd, char *first_occ)
{
	int		cmd_size;
	char	next_char;

	cmd_size = ft_strlen(cmd);
	next_char = next_non_spc_char(cmd_size, first_occ);
	if (check_char(&first_occ[cmd_size]) < 0)
	{
		if (first_occ[cmd_size + 1] == first_occ[cmd_size])
		{
			if (check_char(&first_occ[cmd_size + 2]) == 1
				&& check_closing_quotes(&first_occ[cmd_size]) == 1)
				return (1);
		}
		if (check_char(&first_occ[cmd_size + 1]) == 1
			&& check_closing_quotes(&first_occ[cmd_size]) == 1)
			return (1);
	}
	if (check_char(&first_occ[cmd_size]) == 1 && check_char(&next_char) <= 0)
		return (1);
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

void	echo_n(char **cmd, char *full_arg, int arg_i, int cmd_i)
{
	char	*first_occ;

	while (cmd[cmd_i] != NULL
		&& check_only_redirection(cmd[cmd_i], full_arg) != 2)
	{
		first_occ = ft_strnstr(&full_arg[arg_i], cmd[cmd_i],
				ft_strlen(full_arg));
		if (arg_i == 0)
			space_before_first_arg(full_arg, arg_i);
		while (ft_strcmp(&full_arg[arg_i], first_occ) != 0)
			arg_i++;
		ft_printf("%s", cmd[cmd_i]);
		arg_i = move_arg_i(full_arg, arg_i);
		if (check_if_space_is_needed(cmd[cmd_i], first_occ) == 1)
			ft_printf(" ");
		if (check_char(&full_arg[arg_i]) == 1)
			ft_printf(" ");
		cmd_i++;
	}
}

void	echo(char **cmd, t_data *data, int cmd_i, int arg_i)
{
	char	*first_occ;

	while (cmd[cmd_i] != NULL
		&& check_only_redirection(cmd[cmd_i], data->arg) != 2)
	{
		first_occ = ft_strnstr(&data->arg[arg_i], cmd[cmd_i],
				ft_strlen(data->arg));
		if (arg_i == 0)
			space_before_first_arg(data->arg, arg_i);
		while (ft_strcmp(&data->arg[arg_i], first_occ) != 0)
			arg_i++;
		ft_printf("%s", cmd[cmd_i]);
		arg_i = move_arg_i(data->arg, arg_i);
		if (check_if_space_is_needed(cmd[cmd_i], first_occ) == 1)
			ft_printf(" ");
		if (check_char(&data->arg[arg_i]) == 1)
			ft_printf(" ");
		cmd_i++;
	}
	ft_printf("\n");
}

void	pick_correct_echo(t_cmd *cmd, t_data *data)
{
	int		cmd_i;
	int		arg_i;
	char	*options;

	cmd_i = 1;
	arg_i = 0;
	data->arg = replace_env_in_full_arg(data->arg, data->envp);
	if (check_echo_option(data->arg, cmd->cmd) == 0)
	{
		options = join_echo_options(cmd->cmd, data->arg);
		cmd_i = move_cmd_arr_index(cmd->cmd, options);
		echo_n(cmd->cmd, data->arg, arg_i, cmd_i);
		free(options);
	}
	else
		echo(cmd->cmd, data, cmd_i, arg_i);
}
