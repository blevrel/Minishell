/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:58 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/05 11:05:16 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char *cmd, t_data *data)
{
	if (ft_strcmp(cmd, "cd") == 0)
	{
		directory(data->cmd[0], data);
		data->return_value = 0;
		return (0);
	}
	if (ft_strcmp(cmd, "export") == 0)
	{
		ft_export(data->cmd[0], data);
		data->return_value = 0;
		return (0);
	}
	if (ft_strcmp(cmd, "unset") == 0)
	{
		unset(data->cmd[0], data);
		data->return_value = 0;
		return (0);
	}
	return (1);
}

void	dup_simple_call(t_cmd *cmd)
{
	int	fd;

	if (cmd->outfile != NULL)
	{
		fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd, 1);
		close(fd);
	}
	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			printf("minishell: %s: no such file or directory \n", cmd->infile);
			// a free
			exit (1);
		}
		dup2(fd, 0);
		close(fd);
	}
	if (cmd->outfile_append != NULL)
	{
		fd = open(cmd->outfile_append, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, 1);
		close(fd);
	}
}

int	simple_cmd(t_data *data)
{
	pid_t	son;

	if (builtin(data->cmd[0]->cmd[0], data) == 0)
		return (0);
	ignore_signals();
	son = fork();
	if (son == 0)
	{
		dup_simple_call(data->cmd[0]);
		if (check_builtin(data->cmd[0], data))
		{
			clean_data(data, 1);
			exit (0);
		}
		unset_signals();
		if (execve(data->cmd[0]->path, data->cmd[0]->cmd, data->envp) == -1)
		{
			clean_data(data, 1);
			exit (2);
		}
	}
	return_value(&son, data, 0);
	signal_handler();
	unlink("here_doc");
	return (0);
}
