/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:40:05 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 21:51:17 by blevrel          ###   ########.fr       */
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
}

void	free_simple_cmd(t_cmd *cmd)
{
	if (cmd->path)
		free(cmd->path);
	cmd->path = NULL;
	if (cmd->type)
		free(cmd->type);
	cmd->type = NULL;
	if (cmd->file)
		free(cmd->file);
	cmd->file = NULL;
	free_rest_of_simple_cmd(cmd);
}

void	free_multiple_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i] != NULL)
	{
		free_simple_cmd(data->cmd[i]);
		free(data->cmd[i]);
		data->cmd[i] = NULL;
		++i;
	}
	free(data->cmd);
	data->cmd = NULL;
}

void	free_data(t_data *data)
{
	if (data->parsing && data->parsing[0])
		free_parsing(data);
	free(data->arg);
	free(data->son);
	data->arg = NULL;
	data->son = NULL;
	if (data->cmd)
		free_multiple_cmd(data);
}
