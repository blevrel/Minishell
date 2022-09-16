/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:34:01 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/15 15:39:17 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_file(char **limiter)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open ("here_doc", O_WRONLY | O_CREAT, 0644);
	while (limiter[i] != NULL)
	{
		line = get_next_line(0, 1);
		line[ft_strlen(line) - 1] = 0;
		while (ft_strcmp(line, limiter[i]) != 0)
		{
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
			free(line);
			line = get_next_line(0, 1);
			line[ft_strlen(line) - 1] = 0;
		}
		free(line);
		++i;
	}
	close (fd);
}

void	here_doc(t_cmd *cmd, char **env)
{
	pid_t	son;
	int		fd;

	create_file(cmd->limiter);
	son = fork();
	if (son == 0)
	{
		fd = open ("here_doc", O_RDONLY);
		dup2(fd, 0);
		close(fd);
		if (execve(cmd->path, cmd->cmd, env) == -1)
			exit (1);
	}
	waitpid(son, NULL, 0);
	unlink("here_doc");
}

void	here_doc_pipe(t_cmd *cmd, int **pipexfd, char **env, int i)
{
	pid_t	son;
	int		fd;

	create_file(cmd->limiter);
	(void)env;
	son = fork();
	if (son == 0)
	{
		fd = open ("here_doc", O_RDONLY);
		dup2(fd, 0);
		dup2(pipexfd[i][1], 1);
		close(fd);
		if (execve(cmd->path, cmd->cmd, env) == -1)
			exit (1);
	}
	waitpid(son, NULL, 0);
	close(fd);
	unlink("here_doc");
}
