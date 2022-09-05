/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:22:53 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/05 13:44:23 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fi_pipe(t_cmd *cmd, pid_t son, int **pipexfd, char **env)
{
	pipe(pipexfd[0]);
	son = fork();
	if (son == 0)
	{
		close(pipexfd[0][0]);
		check_dup_pipe_first(cmd, pipexfd, 0);
		close(pipexfd[0][1]);
		execve(cmd->path, cmd->cmd, env);
	}
}

void	n_pipe(t_cmd *cmd, pid_t *son, int **pipexfd, int i, char **env)
{
	pipe(pipexfd[i]);
	son[i] = fork();
	if (son[i] == 0)
	{
		waitpid(son[i - 1], NULL, 0);
		close(pipexfd[i][0]);
		close(pipexfd[i - 1][1]);
		check_dup_pipe_n(cmd, pipexfd, i);
		close(pipexfd[i - 1][0]);
		close(pipexfd[i][1]);
		execve(cmd->path, cmd->cmd, env);
	}
	close(pipexfd[i - 1][1]);
	close(pipexfd[i - 1][0]);
}

void	l_pipe(t_cmd *cmd, pid_t *son, int **pipexfd, char **env, int i)
{
	waitpid(son[i - 1], NULL, 0);
	son[i] = fork();
	if (son[i] == 0)
	{
		close(pipexfd[i - 1][1]);
		check_dup_pipe_last(cmd, pipexfd, i);
		close(pipexfd[i - 1][0]);
		if (execve(cmd->path, cmd->cmd, env) == -1)
			ft_printf("marche pas\n");
	}
	close(pipexfd[i - 1][1]);
	close(pipexfd[i - 1][0]);
	waitpid(son[i], NULL, 0);
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
	int		**pipexfd;
	pid_t	*son;
	int		i;

	i = 0;
	nb_pipe = check_nbpipe(data->cmd);
	data->pipex = init_struct_pipe(data);
	if (!data->pipex)
		return (1);
	pipexfd = malloc_pipe(nb_pipe);
	son = malloc(nb_pipe * sizeof(int));
	fi_pipe(data->pipex[0], son[0], pipexfd, data->envp);
	while (nb_pipe > 1)
	{
		n_pipe(data->pipex[i], son, pipexfd, i, data->envp);
		++i;
		--nb_pipe;
	}
	l_pipe(data->pipex[i], son, pipexfd, data->envp, i);
	return (0);
}
