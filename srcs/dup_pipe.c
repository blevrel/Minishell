/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:16:11 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/09 17:33:52 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_entry(t_cmd *cmd, int **pipexfd, int i)
{
	int	fd;

	if (cmd->outfile)
		fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (cmd->outfile_append)
			fd = open(cmd->outfile_append, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		return ;
	dup2(fd, 1);
	dup2(pipexfd[i][0], 0);
	close(fd);
}

void	check_dup_pipe_first(t_cmd *cmd, int **pipexfd, int i)
{	
	int	fd;

	if (cmd->outfile != NULL || cmd->outfile_append != NULL)
		dup_entry(cmd, pipexfd, i);
	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			printf("minishell : %s: no such file or directory\n", cmd->infile);
			//a free
			exit(1);
		}
		dup2(fd, 0);
		dup2(pipexfd[i][1], 1);
		close(fd);
	}
	else
		dup2(pipexfd[i][1], 1);
}

void	check_dup_pipe_last(t_cmd *cmd, int **pipexfd, int i)
{	
	int	fd;

	if (cmd->outfile != NULL || cmd->outfile_append != NULL)
		dup_entry(cmd, pipexfd, i - 1);
	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	else
		dup2(pipexfd[i - 1][0], 0);
}

void	check_dup_pipe_n(t_cmd *cmd, int **pipexfd, int i)
{	
	int	fd;

	if (cmd->infile != NULL || cmd->outfile != NULL)
		dup_entry(cmd, pipexfd, i - 1);
	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY);
		dup2(fd, 0);
		dup2(pipexfd[i][1], 1);
		close(fd);
	}
	else
	{
		dup2(pipexfd[i -1][0], 0);
		dup2(pipexfd[i][1], 1);
	}
}
