/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokenized_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:03:49 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/02 14:04:36 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	fill_tokenized_cmd_with_quotes(t_data *data, int *i, int *j,
		int cmd_index)
{
	while (data->parsing[cmd_index][*i])
	{
		if (data->parsing[cmd_index][*i] == 34)
		{
			fill_double_quotes(data, i, j, cmd_index);
			(*i)++;
			return ;
		}
		else if (data->parsing[cmd_index][*i] == 39)
		{
			fill_single_quotes(data, i, j, cmd_index);
			(*i)++;
			return ;
		}
	}
}

void	fill_single_quotes(t_data *data, int *i, int *j, int cmd_index)
{
	int	quote;

	quote = 0;
	(*i)++;
	while (data->parsing[cmd_index][*i])
	{
		if (data->parsing[cmd_index][*i] == 39)
			quote = 1;
		if (data->parsing[cmd_index][*i] == 39
			&& data->parsing[cmd_index][*i - 1] == 39
			&& data->parsing[cmd_index][*i - 2] == 39)
		{
			quote = 0;
			(*i)++;
			continue ;
		}
		else if (data->parsing[cmd_index][*i] != 39)
		{
			data->tokenized_str[*j] = data->parsing[cmd_index][*i];
			(*i)++;
			(*j)++;
		}
		if (quote == 1)
			return ;
	}
}

void	fill_double_quotes(t_data *data, int *i, int *j, int cmd_index)
{
	int	quote;

	quote = 0;
	(*i)++;
	while (data->parsing[cmd_index][*i])
	{
		if (data->parsing[cmd_index][*i] == 34)
			quote = 1;
		if (data->parsing[cmd_index][*i] == 34
			&& data->parsing[cmd_index][*i - 1] == 34
			&& data->parsing[cmd_index][*i - 2] == 34)
		{
			quote = 0;
			(*i)++;
			continue ;
		}
		if (data->parsing[cmd_index][*i] == '$')
			get_env_variable(data, i, j, cmd_index);
		else if (data->parsing[cmd_index][*i] != 34)
		{
			data->tokenized_str[*j] = data->parsing[cmd_index][*i];
			(*i)++;
			(*j)++;
		}
		if (quote == 1)
			return ;
	}
}
