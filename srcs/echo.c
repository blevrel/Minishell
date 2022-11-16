/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:53 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 17:03:35 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	echo_n(char **cmd, t_data *data, int cmd_i, char *tok_arg)
{
	char	*first_occ;
	int		arg_i;

	arg_i = 0;
	while (cmd[++cmd_i] != NULL && (!cmd[cmd_i][0]
		|| get_arg_type(data, cmd[cmd_i], tok_arg, -1) != 2))
	{
		if (!cmd[cmd_i][0])
			continue ;
		first_occ = ft_strnstr_skip_quotes(&tok_arg[arg_i], cmd[cmd_i],
				ft_strlen(tok_arg));
		if (arg_i == 0)
			space_before_first_arg(tok_arg, arg_i);
		while (ft_strcmp(&tok_arg[arg_i], first_occ) != 0)
			arg_i++;
		ft_printf("%s", cmd[cmd_i]);
		while (tok_arg[arg_i] && check_char(&tok_arg[arg_i]) == 0)
			arg_i++;
		if (check_if_space_is_needed(cmd[cmd_i], first_occ) == 1)
			ft_printf(" ");
	}
}

void	echo(char **cmd, t_data *data, int cmd_i, char *tok_arg)
{
	char	*first_occ;
	int		arg_i;

	arg_i = 0;
	while (cmd[++cmd_i] != NULL && (!cmd[cmd_i][0]
		|| get_arg_type(data, cmd[cmd_i], tok_arg, -1) != 2))
	{
		if (!cmd[cmd_i][0])
			continue ;
		first_occ = ft_strnstr_skip_quotes(&tok_arg[arg_i], cmd[cmd_i],
				ft_strlen(tok_arg));
		if (arg_i == 0)
			space_before_first_arg(tok_arg, arg_i);
		while (tok_arg[arg_i] && ft_strcmp(&tok_arg[arg_i], first_occ) != 0)
			arg_i++;
		ft_printf("%s", cmd[cmd_i]);
		while (tok_arg[arg_i] && check_char(&tok_arg[arg_i]) == 0)
			arg_i++;
		if (check_if_space_is_needed(cmd[cmd_i], first_occ) == 1)
			ft_printf(" ");
	}
	ft_printf("\n");
}

void	pick_correct_echo(t_cmd *cmd, t_data *data)
{
	int		cmd_i;
	char	*options;
	char	*tok_arg;

	cmd_i = 0;
	tok_arg = tokenize_full_arg(data->arg, data);
	if (check_echo_option(tok_arg, cmd->cmd) == 0)
	{
		options = join_echo_options(cmd->cmd, tok_arg);
		cmd_i = move_cmd_arr_index(cmd->cmd, options);
		echo_n(cmd->cmd, data, cmd_i, tok_arg);
		free(options);
	}
	else
		echo(cmd->cmd, data, cmd_i, tok_arg);
}
