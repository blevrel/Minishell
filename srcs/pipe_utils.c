/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:22:53 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/02 10:35:16 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fi_pipe(t_data *data)
{
	pipe(data->pipexfd[0]);
	data->son[0] = fork();
	if (data->son[0] == 0)
	{
		close(data->pipexfd[0][0]);
		check_dup_pipe_first(data->cmd[0], data->pipexfd, 0, data);
		close(data->pipexfd[0][1]);
		if (check_builtin(data->cmd[0], data))
		{
			clean_data(data, 1);
			exit (1);
		}
		if (execve(data->cmd[0]->path, data->cmd[0]->cmd, data->envp) == -1)
			exit(2);
	}
}

void	n_pipe(t_data *data, int i)
{
	pipe(data->pipexfd[i]);
	data->son[i] = fork();
	if (data->son[i] == 0)
	{
		close(data->pipexfd[i][0]);
		close(data->pipexfd[i - 1][1]);
		check_dup_pipe_n(data->cmd[i], data->pipexfd, i, data);
		close(data->pipexfd[i - 1][0]);
		close(data->pipexfd[i][1]);
		if (check_builtin(data->cmd[i], data))
		{
			clean_data(data, 1);
			exit (1);
		}
		if (execve(data->cmd[i]->path, data->cmd[i]->cmd, data->envp) == -1)
			exit (2);
	}
	close(data->pipexfd[i - 1][1]);
	close(data->pipexfd[i - 1][0]);
}

void	l_pipe(t_data *data, int i)
{
	data->son[i] = fork();
	if (data->son[i] == 0)
	{
		close(data->pipexfd[i - 1][1]);
		check_dup_pipe_last(data->cmd[i], data->pipexfd, i, data);
		close(data->pipexfd[i - 1][0]);
		if (check_builtin(data->cmd[i], data))
		{
			clean_data(data, 1);
			exit (1);
		}
		if (execve(data->cmd[i]->path, data->cmd[i]->cmd, data->envp) == -1)
			exit(2);
	}
	close(data->pipexfd[i - 1][1]);
	close(data->pipexfd[i - 1][0]);
}

int	**malloc_pipe(int argc)
{
	int	**pipexfd;
	int	i;

	i = 0;
	pipexfd = malloc(argc * sizeof(int *));
	if (verif_malloc_int_arr(pipexfd) == 1)
		return (NULL);
	while (i < argc)
	{
		pipexfd[i] = malloc(2 * sizeof(int));
		if (verif_malloc_int(pipexfd, i) == 1)
			return (NULL);
		i++;
	}
	return (pipexfd);
}
