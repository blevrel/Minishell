/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:16:11 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/08 17:49:31 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dup_pipe_first(t_cmd *cmd, int **pipexfd, int i)
{	
	int	fd;

	if (ft_strcmp(cmd->type, ">") == 0)
	{
		fd = open(cmd->file, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		dup2(fd, 1);
		close(fd);
	}
	else if (ft_strcmp(cmd->type, "<") == 0)
	{
		fd = open(cmd->file, O_RDONLY);
		dup2(fd, 0);
		dup2(pipexfd[i][1], 1);
		close(fd);
	}
	else if (ft_strcmp(cmd->type, ">>") == 0)
	{
		fd = open(cmd->file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		dup2(fd, 1);
		close(fd);
	}
	else if (ft_strcmp(cmd->type, "<<") == 0)
		exit (1);
	else
		dup2(pipexfd[i][1], 1);
}

void	check_dup_pipe_last(t_cmd *cmd, int **pipexfd, int i)
{	
	int	fd;

	if (ft_strcmp(cmd->type, ">") == 0)
	{
		fd = open(cmd->file, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		dup2(fd, 1);
		dup2(pipexfd[i - 1][0], 0);
		close(fd);
	}
	else if (ft_strcmp(cmd->type, "<") == 0)
	{
		fd = open(cmd->file, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	else if (ft_strcmp(cmd->type, ">>") == 0)
	{
		fd = open(cmd->file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		dup2(fd, 1);
		dup2(pipexfd[i - 1][0], 0);
		close(fd);
	}
	else if (ft_strcmp(cmd->type, "<<") == 0)
		exit (1);
	else
		dup2(pipexfd[i - 1][0], 0);
}

void	check_dup_pipe_n(t_cmd *cmd, int **pipexfd, int i)
{	
	int	fd;

	if (ft_strcmp(cmd->type, ">") == 0)
	{
		fd = open(cmd->file, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		dup2(fd, 1);
		dup2(pipexfd[i - 1][0], 0);
		close(fd);
	}
	else if (ft_strcmp(cmd->type, "<") == 0)
	{
		fd = open(cmd->file, O_RDONLY);
		dup2(fd, 0);
		dup2(pipexfd[i][1], 1);
		close(fd);
	}
	else if (ft_strcmp(cmd->type, ">>") == 0)
	{
		fd = open(cmd->file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		dup2(fd, 1);
		dup2(pipexfd[i - 1][0], 0);
		close(fd);
	}
	else if (ft_strcmp(cmd->type, "<<") == 0)
		exit (1);
	else
	{
		dup2(pipexfd[i -1][0], 0);
		dup2(pipexfd[i][1], 1);
	}
}
