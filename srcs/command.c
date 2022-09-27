/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:58 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/27 11:48:44 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*cmd_not_found(char *cmd)
{
	if (ft_strchr_int(cmd, '/') != 0)
		printf("%s: No such file or directory\n", cmd);
	else
		printf("%s: command not found\n", cmd);
	return (NULL);
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

	if (ft_strcmp(data->cmd[0]->cmd[0], "cd") == 0)
		directory(data->cmd[0], data);
	if (ft_strcmp(data->cmd[0]->cmd[0], "export") == 0)
		ft_export(data->cmd[0], data);
		
	if (ft_strcmp(data->cmd[0]->cmd[0], "unset") == 0)
		unset(data->cmd[0], data);
	if (ft_strcmp(data->cmd[0]->type, "<<") == 0)
	{
		here_doc(data->cmd[0], data->envp);
		return (0);
	}
	son = fork();
	if (son == 0)
	{
		dup_simple_call(data->cmd[0]->type, data->cmd[0]->file);
		if (check_builtin(data->cmd[0], data))
			exit (1);
		if (execve(data->cmd[0]->path, data->cmd[0]->cmd, data->envp) == -1)
			exit (2);
	}
	waitpid(son, NULL, 0);
	
	return (0);
}
