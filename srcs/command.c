/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:58 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/27 18:07:27 by pirabaud         ###   ########.fr       */
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
	if (ft_strcmp(data->cmd[0]->type, "<<") == 0)
	{
		here_doc(data->cmd[0], data->envp);
		return (0);
	}
	if (ft_strcmp(cmd, "echo") == 0)
	{
		pick_correct_echo(data->cmd[0], data);
		return (0);
	}
	return (1);
}

void	dup_simple_call(char *type, char *file)
{
	int	fd;

	if (ft_strcmp(type, ">") == 0)
	{
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		dup2(fd, 1);
		close(fd);
	}
	else if (ft_strcmp(type, "<") == 0)
	{
		fd = open(file, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	else if (ft_strcmp(type, ">>") == 0)
	{
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
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
	son = fork();
	g_signal_trigger = IN_COMMAND;
	if (son == 0)
	{
		g_signal_trigger = IN_COMMAND;
		signal_handler();
		dup_simple_call(data->cmd[0]->type, data->cmd[0]->file);
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
