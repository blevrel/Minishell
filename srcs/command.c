/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:58 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/29 12:00:38 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char *cmd, t_data *data)
{
	if (ft_strcmp(cmd, "cd") == 0)
	{
		directory(data->cmd[0], data);
		return (0);
	}
	if (ft_strcmp(cmd, "export") == 0)
	{
		ft_export(data->cmd[0], data);
		return (0);
	}
	if (ft_strcmp(cmd, "unset") == 0)
	{
		unset(data->cmd[0], data);
		return (0);
	}
	if (data->cmd[0]->heredoc == 1)
	{
		here_doc(data->cmd[0], data);
		return (0);
	}

	return (1);
}

void	dup_simple_call(t_cmd *cmd)
{
	int	fd;

	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd, 1);
		close(fd);
	}
	if (cmd->outfile != NULL)
	{
		fd = open(cmd->outfile, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	if (cmd->infile_append != NULL)
	{
		fd = open(cmd->infile_append, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, 1);
		close(fd);
	}
	else
		return ;
}

int	simple_cmd(t_data *data)
{
	pid_t	son;

	if (builtin(data->cmd[0]->cmd[0], data) == 0)
	{
		data->return_value = 0;
		return (0);
	}
	g_signal_trigger = IN_COMMAND;
	son = fork();
	if (son == 0)
	{
		dup_simple_call(data->cmd[0]);
		if (check_builtin(data->cmd[0], data))
		{
			free_data(data);
			free_double_tab(data->envp);
			free_double_tab(data->export);
			free(data);
			exit (0);
		}
		if (execve(data->cmd[0]->path, data->cmd[0]->cmd, data->envp) == -1)
			exit (2);
	}
	return_value(&son, data, 0);
	return (0);
}
