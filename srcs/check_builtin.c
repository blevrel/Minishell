/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:12:18 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 14:59:37 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
	{
		data->return_value = 0;
		pick_correct_echo(cmd, data);
		return (1);
	}
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
	{
		data->return_value = 0;
		pwd();
		return (1);
	}
	if (ft_strcmp(cmd->cmd[0], "env") == 0)
	{
		data->return_value = 0;
		env(data->envp);
		return (1);
	}
	return (0);
}

int	check_builtin_pipe(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		pick_correct_echo(cmd, data);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		env(data->envp);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		ft_export(cmd, data);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		unset(cmd, data);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		directory(cmd, data);
	else
		return (0);
	data->return_value = 0;
	return (1);
}
