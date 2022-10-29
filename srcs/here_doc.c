/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:34:01 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/29 11:43:30 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*tokenize_here_doc_line(t_data *data)
{
	int		i;
	int		j;
	char	*line;
	char	*new_line;
	
	i = 0;
	j = 0;
	line = readline("");
	if (line == NULL)
		exit(50);
	new_line = malloc((size_here_doc_line(line, data) + 1) * sizeof(char));
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '$'
			&& check_char(&line[i + 1]) >= 0)
		{
			fill_env(new_line, &line[i], data, &j);
			move_indextoenv(line, &i);
		}
		else
			ft_fill_char_and_increment(new_line, line, &i, &j);
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

void	create_file(char **limiter, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open ("here_doc", O_WRONLY | O_CREAT, 0644);
	while (limiter[i] != NULL)
	{
		line = tokenize_here_doc_line(data);
		while (ft_strcmp(line, limiter[i]) != 0)
		{
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
			free(line);
			line = tokenize_here_doc_line(data);
		}
		free(line);
		++i;
	}
	close (fd);
}

void	here_doc(t_cmd *cmd, t_data *data)
{
	int		fd;

	g_signal_trigger = IN_HERE_DOC;
	signal_handler();
	create_file(cmd->limiter, data);
	if (cmd->outfile != NULL)
	{
		fd = open ("here_doc", O_RDONLY);
		dup2(fd, 0);
		close(fd);
		if (execve(cmd->path, cmd->cmd, data->envp) == -1)
		{
			clean_data(data, 1);
			exit (1);
		}
	}
	//waitpid(son, NULL, 0);
	//unlink("here_doc");
}

void	here_doc_pipe(t_cmd *cmd, int **pipexfd, t_data *data, int i)
{
	pid_t	son;
	int		fd;

	son = fork();
	if (son == 0)
	{
		g_signal_trigger = IN_HERE_DOC;
		signal_handler();
		create_file(cmd->limiter, data);
		fd = open ("here_doc", O_RDONLY);
		close(pipexfd[i][0]);
		dup2(fd, 0);
		dup2(pipexfd[i][1], 1);
		close(fd);
		if (execve(cmd->path, cmd->cmd, data->envp) == -1)
		{
			clean_data(data, 1);
			exit (1);
		}
	}
	waitpid(son, NULL, 0);
	close(fd);
	unlink("here_doc");
}
