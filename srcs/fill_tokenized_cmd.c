/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokenized_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:03:49 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/08 17:28:32 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	fill_tokenized_cmd_with_quotes(t_data *data, int *i, int *j,
		int cmd_index)
{
	while (data->cmd[cmd_index][*i])
	{
		if (data->cmd[cmd_index][*i] == 34)
		{
			fill_double_quotes(data, i, j, cmd_index);
			(*i)++;
			return ;
		}
		else if (data->cmd[cmd_index][*i] == 39)
		{
			fill_single_quotes(data, i, j, cmd_index);
			(*i)++;
			return ;
		}
	}
}

void	fill_single_quotes(t_data *data, int *i, int *j, int cmd_index)
{
	(*i)++;
	while (data->cmd[cmd_index][*i] != 39)
	{
		data->tokenized_str[*j] = data->cmd[cmd_index][*i];
		(*i)++;
		(*j)++;
	}
}

void	fill_double_quotes(t_data *data, int *i, int *j, int cmd_index)
{
	(*i)++;
	while (data->cmd[cmd_index][*i] && data->cmd[cmd_index][*i] != 34)
	{
		if (data->cmd[cmd_index][*i] == '$')
		{
			get_env_variable(data, i, j, cmd_index);
			while (data->cmd[cmd_index][*i]
				&& check_char(data->cmd[cmd_index][*i]) >= 0)
				(*i)++;
		}
		else
		{
			data->tokenized_str[*j] = data->cmd[cmd_index][*i];
			(*i)++;
			(*j)++;
		}
	}
}
