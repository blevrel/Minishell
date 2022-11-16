/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:22:53 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 20:03:50 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	close_pipes(t_data *data, int i)
{
	close(data->pipexfd[i - 1][1]);
	close(data->pipexfd[i - 1][0]);
}

void	fi_pipe(t_data *data)
{
	int	ret;

	close(data->pipexfd[0][0]);
	check_dup_pipe_first(data->cmd[0], data->pipexfd, 0, data);
	close(data->pipexfd[0][1]);
	if (check_builtin_pipe(data->cmd[0], data))
	{
		free_pipex(data->pipexfd, check_nbpipe(data->arg));
		ret = data->return_value;
		clean_data(data, 1);
		exit(ret);
	}
	unset_signals();
	data->cmd[0]->path = check_path(data->cmd[0]->cmd[0], data);
	if (data->cmd[0]->path)
		if (execve(data->cmd[0]->path, data->cmd[0]->cmd, data->envp) == -1)
				data->return_value = 2;
	free_pipex(data->pipexfd, check_nbpipe(data->arg));
	ret = data->return_value;
	clean_data(data, 1);
	exit(ret);
}

void	n_pipe(t_data *data, int i)
{
	int	ret;

	close(data->pipexfd[i][0]);
	close(data->pipexfd[i - 1][1]);
	check_dup_pipe_n(data->cmd[i], data->pipexfd, i, data);
	close(data->pipexfd[i - 1][0]);
	close(data->pipexfd[i][1]);
	if (check_builtin_pipe(data->cmd[i], data))
	{
		free_pipex(data->pipexfd, check_nbpipe(data->arg));
		ret = data->return_value;
		clean_data(data, 1);
		exit(ret);
	}
	unset_signals();
	data->cmd[i]->path = check_path(data->cmd[i]->cmd[0], data);
	if (data->cmd[i]->path)
		if (execve(data->cmd[i]->path, data->cmd[i]->cmd, data->envp) == -1)
			data->return_value = 2;
	free_pipex(data->pipexfd, check_nbpipe(data->arg));
	ret = data->return_value;
	clean_data(data, 1);
	exit(ret);
}

void	l_pipe(t_data *data, int i)
{
	int	ret;

	close(data->pipexfd[i - 1][1]);
	check_dup_pipe_last(data->cmd[i], data->pipexfd, i, data);
	close(data->pipexfd[i - 1][0]);
	if (check_builtin_pipe(data->cmd[i], data))
	{
		free_pipex(data->pipexfd, check_nbpipe(data->arg));
		ret = data->return_value;
		clean_data(data, 1);
		exit(ret);
	}
	unset_signals();
	data->cmd[i]->path = check_path(data->cmd[i]->cmd[0], data);
	if (data->cmd[i]->path)
		if (execve(data->cmd[i]->path, data->cmd[i]->cmd, data->envp) == -1)
			data->return_value = 2;
	free_pipex(data->pipexfd, check_nbpipe(data->arg));
	ret = data->return_value;
	clean_data(data, 1);
	exit(ret);
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
