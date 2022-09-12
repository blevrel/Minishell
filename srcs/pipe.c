/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:22:53 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/12 09:42:54 by pirabaud         ###   ########.fr       */
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
		check_dup_pipe_first(data->pipex[0], data->pipexfd, 0);
		close(data->pipexfd[0][1]);
		if (execve(data->pipex[0]->path, data->pipex[0]->cmd, data->envp) == -1)
			printf("marche po\n");
	}
	waitpid(data->son[0], NULL, 0);
}

void	n_pipe(t_data *data, int i)
{
	pipe(data->pipexfd[i]);
	data->son[i] = fork();
	if (data->son[i] == 0)
	{
		waitpid(data->son[i - 1], NULL, 0);
		close(data->pipexfd[i][0]);
		close(data->pipexfd[i - 1][1]);
		check_dup_pipe_n(data->pipex[i], data->pipexfd, i);
		close(data->pipexfd[i - 1][0]);
		close(data->pipexfd[i][1]);
		execve(data->pipex[i]->path, data->pipex[i]->cmd, data->envp);
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
		check_dup_pipe_last(data->pipex[i], data->pipexfd, i);
		close(data->pipexfd[i - 1][0]);
		if (execve(data->pipex[i]->path, data->pipex[i]->cmd, data->envp) == -1)
			ft_printf("marche pas\n");
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
	nb_pipe = check_nbpipe(data->cmd);
	data->pipex = init_struct_pipe(data);
	if (!data->pipex)
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
