/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_call_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:06:07 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/29 11:44:53 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char **init_cmd(t_data *data, int index_pipe)
{
	char **res;
	nb_pipe;
	
	nb_pipe = 0;
	while (data->cmd[i] != NULL && nb_pipe != index_pipe)
	{
		if (ft_strcmp(data->cmd[i],"|"))
			++nb_pipe
		++i;
	}
	check_nbtab(&data->cmd[i]);
}

int	first_simple_call(int *pipexfd, t_data *data)
{
	char *path;
	char **cmd;

	if (check_builtin_first(pipexfd, data, 0) == 1)
		return (0);
	path = check_path(data->cmd[0], data->envp);
	if (path == NULL)
	{
		cmd_not_found(data->cmd[0]);
		return (1);	
	}
	cmd = init_cmd(data, i);
	int i = 0;
	printf("path first : %s\n", path);
	while(data->cmd_pipe[i] !=  NULL)
	{
			printf("cmd first %d:, %s\n", i, data->cmd_pipe[i]);
			++i;
	}
	data->son[0] = fork();
	if (data->son[0] == 0)
	{
		dup2(pipexfd[1], 1);
		execve(path, data->cmd_pipe, data->envp);
	}
	free(path);
	return (0);
}

int	mid_simple_call(int *pipe, int *pipenext, t_data *data, int i)
{
	char *path;
	
	if (check_builtin_mid(pipe, pipenext, data, i) == 1)
		return (0);
	path = check_path(data->cmd[0], data->envp);
	if (path == NULL)
	{
		cmd_not_found(data->cmd[0]);
		return (1);
	}
	data->son[i] = fork();
	if (data->son[i] == 0)
	{
		waitpid(data->son[i - 1], NULL, 0);
		close(pipenext[0]);
		close(pipe[1]);
		dup2(pipe[0], 0);
		dup2(pipenext[1], 1);
		execve(path, data->cmd_pipe, data->envp);
	}
	free(path);
	return (0);
}

int	last_simple_call(int *pipe,int i, t_data *data)
{
	char *path;
	char **cmd;
	
	if (check_builtin_last(pipe, data, i))
		return (0);
	path = check_path(data->cmd[0], data->envp);
	if (path == NULL)
	{
		cmd_not_found(data->cmd[0]);
		return (1);
	}
	cmd = init_cmd(data, i);
	int j = 0;
	printf("path last : %s\n", path);
	while(cmd  !=  NULL)
	{
			printf("cmd last j%d: %s\n", j, cmd[j]);
			++j;
	}
	data->son[i] = fork();
	if (data->son[i] == 0)
	{
		waitpid(data->son[i -1], NULL, 0);
		close(pipe[1]);
		dup2(pipe[0], 0);
		execve(path, data->cmd_pipe, data->envp);
	}
	free(path);
	return (1);
}
