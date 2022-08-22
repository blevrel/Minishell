/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:34:01 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/22 14:19:31 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_file(t_data *data)
{
	int		fd;
	char	*line;

	fd = open ("here_doc", O_WRONLY | O_CREAT, S_IRWXU);
	line = get_next_line(0, 1);
	line[ft_strlen(line) - 1] = 0;
	while (ft_strcmp(line, data->cmd[1]))
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = get_next_line(0, 1);
		line[ft_strlen(line) - 1] = 0;
	}
	free(line);
	return (fd);
}

void	append(t_data *data)
{
	pid_t	son;
	char	*path;
	int		i;
	int		fd;
	char	**arg;

	path = check_path(data->cmd[0], data->envp);
	arg = check_arg(data->cmd, '>');
	son = fork();
	if (son == 0)
	{
		i = 0;
		while (ft_strcmp(data->cmd[i], ">>") != 0)
			++i;
		fd = open(data->cmd[i + 1], O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		if (fd == -1)
			printf("file simple red entry");
		dup2(fd, 1);
		close (fd);
		execve(path, arg, data->envp);
		exit(0);
	}
	waitpid(son, NULL, 0);
}

void	here_doc(t_data *data)
{
	pid_t	son;
	char	*path;
	int		fd;

	path = check_path(data->cmd[0], data->envp);
	fd = create_file(data);
	son = fork();
	if (son == 0)
	{
		dup2(fd, 0);
		close(fd);
		execve(path, data->cmd, data->envp);
	}
	waitpid(son, NULL, 0);
	close(fd);
}

void	entry_red(t_data *data)
{
	pid_t	son;
	char	*path;
	int		i;
	int		fd;

	path = check_path(data->cmd[0], data->envp);
	i = 0;
	son = fork();
	if (son == 0)
	{
		while (ft_strcmp(data->cmd[i], "<") != 0)
			++i;
		fd = open(data->cmd[i + 1], O_RDONLY);
		if (fd == -1)
			printf("file simple red entry");
		dup2(fd, 0);
		close (fd);
		execve(path, data->cmd, data->envp);
		exit(1);
	}
	waitpid(son, NULL, 0);
}

void	exit_red(t_data *data)
{
	pid_t	son;
	char	*path;
	int		i;
	int		fd;
	char	**arg;

	path = check_path(data->cmd[0], data->envp);
	arg = check_arg(data->cmd, '>');
	son = fork();
	if (son == 0)
	{
		i = 0;
		while (ft_strcmp(data->cmd[i], ">") != 0)
			++i;
		fd = open(data->cmd[i + 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		if (fd == -1)
			printf("file simple red entry");
		dup2(fd, 1);
		close (fd);
		execve(path, arg, data->envp);
		exit(1);
	}
	waitpid(son, NULL, 0);
}
