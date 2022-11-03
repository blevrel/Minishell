/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:12:18 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/02 14:17:24 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
	{
		pick_correct_echo(cmd, data);
		return (1);
	}
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
	{
		pwd();
		return (1);
	}
	if (ft_strcmp(cmd->cmd[0], "env") == 0)
	{
		env(data->envp);
		return (1);
	}
	if (data->cmd[0]->heredoc == 1)
	{
		here_doc(data->cmd[0], data);
		return (0);
	}
	return (0);
}

int	check_builtin_pipe(t_cmd *cmd, int **pipexfd, t_data *data, int i)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
	{
		pick_correct_echo(cmd, data);
		return (1);
	}
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
	{
		pwd();
		return (1);
	}
	if (ft_strcmp(cmd->cmd[0], "env") == 0)
	{
		env(data->envp);
		return (1);
	}
	if (data->cmd[0]->heredoc == 1)
	{
		here_doc_pipe(data->cmd[0], pipexfd, data, i);
		return (0);
	}
	return (0);
}
