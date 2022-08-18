/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:34:01 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/18 10:30:29 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	entry_red(t_data data)
{
	pid_t	son;
	char	*path;
	int		i;
	int		fd;

	path = check_path(data.cmd[0], data.envp);
	i = 0;
	son = fork();
	if (son == 0)
	{
		while (ft_strcmp(data.cmd[i], "<") != 0)
			++i;
		fd = open(data.cmd[i + 1], O_RDONLY);
		if (fd == -1)
			printf("file simple red entry");
		dup2(fd, 0);
		close (fd);
		execve(path, data.cmd, data.envp);
	}
	waitpid(son, NULL, 0);
}

void	exit_red(t_data data)
{
	pid_t	son;
	char	*path;
	int		i;
	int		fd;

	path = check_path(data.cmd[0], data.envp);
	son = fork();
	if (son == 0)
	{
		i = 0;
		while (ft_strcmp(data.cmd[i], ">") != 0)
			++i;
		fd = open(data.cmd[i + 1], O_WRONLY | O_CREAT, S_IRWXU);
		if (fd == -1)
			printf("file simple red entry");
		dup2(fd, 1);
		close (fd);
		execve(path, data.cmd, data.envp);
	}
	waitpid(son, NULL, 0);
}
