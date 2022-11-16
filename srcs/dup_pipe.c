/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:16:11 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 14:12:01 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_entry(t_cmd *cmd, t_data *data)
{
	int	fd;

	if (cmd->outfile)
		fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(cmd->outfile_append, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		free_pipex(data->pipexfd, check_nbpipe(data->arg));
		clean_data(data, 1);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	check_dup_pipe_first(t_cmd *cmd, int **pipexfd, int i, t_data *data)
{	
	int	fd;

	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			free_pipex(pipexfd, check_nbpipe(data->arg));
			clean_data(data, 1);
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
	if (cmd->outfile != NULL || cmd->outfile_append != NULL)
	{
		dup_entry(cmd, data);
	}
	else
		dup2(pipexfd[i][1], 1);
}

void	check_dup_pipe_last(t_cmd *cmd, int **pipexfd, int i, t_data *data)
{	
	int	fd;

	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			clean_data(data, 1);
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
	else
		dup2(pipexfd[i - 1][0], 0);
	if (cmd->outfile != NULL || cmd->outfile_append != NULL)
		dup_entry(cmd, data);
}

void	check_dup_pipe_n(t_cmd *cmd, int **pipexfd, int i, t_data *data)
{	
	int	fd;

	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			clean_data(data, 1);
			exit(1);
		}
		dup2(fd, 0);
		dup2(pipexfd[i][1], 1);
		close(fd);
	}
	else
		dup2(pipexfd[i -1][0], 0);
	if (cmd->outfile_append != NULL || cmd->outfile != NULL)
		dup_entry(cmd, data);
	else
		dup2(pipexfd[i][1], 1);
}
