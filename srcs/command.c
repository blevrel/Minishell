/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:58 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 14:34:32 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char *cmd, t_data *data)
{
	if (ft_strcmp(cmd, "cd") == 0)
	{
		data->return_value = 0;
		directory(data->cmd[0], data);
		return (0);
	}
	if (ft_strcmp(cmd, "export") == 0)
	{
		data->return_value = 0;
		ft_export(data->cmd[0], data);
		return (0);
	}
	if (ft_strcmp(cmd, "unset") == 0)
	{
		data->return_value = 0;
		unset(data->cmd[0], data);
		return (0);
	}
	return (1);
}

void	dup_fd_outfile(t_cmd *cmd, t_data *data)
{
	int	fd;

	if (cmd->outfile_append != NULL)
		fd = open(cmd->outfile_append, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmd->outfile != NULL)
		fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		clean_data(data, 1);
		exit (1);
	}
	dup2(fd, 1);
	close(fd);
}

void	dup_simple_call(t_cmd *cmd, t_data *data)
{
	int	fd;

	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			clean_data(data, 1);
			exit (1);
		}
		dup2(fd, 0);
		close(fd);
	}
	if (cmd->outfile_append != NULL || cmd->outfile != NULL)
		dup_fd_outfile(cmd, data);
}

void	child_simple_cmd(t_data *data)
{
	int		ret_value;

	dup_simple_call(data->cmd[0], data);
	if (check_builtin(data->cmd[0], data))
	{
		clean_data(data, 1);
		exit (data->return_value);
	}
	unset_signals();
	data->cmd[0]->path = check_path(data->cmd[0]->cmd[0], data);
	if (data->cmd[0]->path)
		if (execve(data->cmd[0]->path, data->cmd[0]->cmd, data->envp) == -1)
			data->return_value = 2;
	ret_value = data->return_value;
	clean_data(data, 1);
	exit (ret_value);
}

int	simple_cmd(t_data *data)
{
	pid_t	son;

	if (builtin(data->cmd[0]->cmd[0], data) == 0)
		return (0);
	ignore_signals();
	son = fork();
	if (son == 0)
		child_simple_cmd(data);
	else if (son < 0)
		ft_print_error("fork failed\n");
	return_value(&son, data, 1);
	signal_handler();
	unlink("here_doc");
	return (0);
}
