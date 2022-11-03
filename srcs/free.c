/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:40:05 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/03 14:55:32 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parsing(t_data *data)
{
	int	i;

	i = 0;
	while (data->parsing[i])
	{
		free(data->parsing[i]);
		data->parsing[i] = NULL;
		i++;
	}
	free(data->parsing);
	data->parsing = NULL;
}

void	free_rest_of_simple_cmd(t_cmd *cmd)
{
	int	j;

	j = 0;
	if (cmd->limiter)
	{
		while (cmd->limiter[j])
		{
			free(cmd->limiter[j]);
			j++;
		}
		free(cmd->limiter);
		cmd->limiter = NULL;
	}
	j = 0;
	while (cmd->cmd[j])
	{
		free(cmd->cmd[j]);
		j++;
	}
	free(cmd->cmd);
	cmd->cmd = NULL;
	free(cmd);
	cmd = NULL;
}

void	free_simple_cmd(t_cmd *cmd)
{
	if (cmd->path)
		free(cmd->path);
	cmd->path = NULL;
	free_file(cmd);
	free_rest_of_simple_cmd(cmd);
}

void	free_multiple_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		free_simple_cmd(cmd[i]);
		cmd[i] = NULL;
		++i;
	}
	free(cmd);
	cmd = NULL;
}

void	clean_data(t_data *data, int trigger)
{
	if (data->parsing)
		free_parsing(data);
	free(data->arg);
	free(data->son);
	data->arg = NULL;
	data->son = NULL;
	if (data->cmd)
		free_multiple_cmd(data->cmd);
	if (trigger == 1)
	{
		free_double_tab(data->envp);
		free_double_tab(data->export);
		free(data);
	}
}
