/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:22:53 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/14 15:24:26 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fi_pipe(t_data *data)
{
	pipe(data->pipexfd[0]);
	data->son[0] = fork();
	if (data->son[0] == 0)
	{
		if (ft_strcmp(data->cmd[0]->type, "<<") == 0)
		{
			here_doc_pipe(data->cmd[0], data->pipexfd, data->envp, 0);
			exit(1);
		}
		close(data->pipexfd[0][0]);
		check_dup_pipe_first(data->cmd[0], data->pipexfd, 0);
		close(data->pipexfd[0][1]);
		if (execve(data->cmd[0]->path, data->cmd[0]->cmd, data->envp) == -1)
			exit(2);
	}
	waitpid(data->son[0], NULL, 0);
}

void	n_pipe(t_data *data, int i)
{
	pipe(data->pipexfd[i]);
	data->son[i] = fork();
	if (data->son[i] == 0)
	{
		if (ft_strcmp(data->cmd[0]->type, "<<") == 0)
		{
			here_doc_pipe(data->cmd[0], data->pipexfd, data->envp, i);
			exit(1);
		}
		waitpid(data->son[i - 1], NULL, 0);
		close(data->pipexfd[i][0]);
		close(data->pipexfd[i - 1][1]);
		check_dup_pipe_n(data->cmd[i], data->pipexfd, i);
		close(data->pipexfd[i - 1][0]);
		close(data->pipexfd[i][1]);
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
		if (ft_strcmp(data->cmd[0]->type, "<<") == 0)
		{
			here_doc_pipe(data->cmd[0], data->pipexfd, data->envp, i);
			exit(1);
		}
		close(data->pipexfd[i - 1][1]);
		check_dup_pipe_last(data->cmd[i], data->pipexfd, i);
		close(data->pipexfd[i - 1][0]);
		if (execve(data->cmd[i]->path, data->cmd[i]->cmd, data->envp) == -1)
			exit(2);
	}
	close(data->pipexfd[i - 1][1]);
	close(data->pipexfd[i - 1][0]);
	waitpid(data->son[i], NULL, 0);
}

int	**malloc_pipe(int argc)
{
	int	**pipexfd;
	int	i;

	i = 0;
	pipexfd = malloc(argc * sizeof(int *));
	while (i < argc)
		pipexfd[i++] = malloc(2 * sizeof(int));
	return (pipexfd);
}

int	ft_pipe(t_data *data)
{
	int		nb_pipe;
	int		i;

	i = 1;
	nb_pipe = check_nbpipe(data->parsing);
	if (!data->cmd)
		return (1);
	data->pipexfd = malloc_pipe(nb_pipe);
	data->son = malloc(nb_pipe * sizeof(int));
	fi_pipe(data);
	while (nb_pipe > 1)
	{
		n_pipe(data, i);
		++i;
		--nb_pipe;
	}
	l_pipe(data, i);
	return (0);
}
