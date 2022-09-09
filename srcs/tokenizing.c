/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:21 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/09 11:29:43 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
/*
trouver un moyen de laisser un repere pour que les redirections entre
quotes ne soient pas interpretées.
*/

void	tokenize(t_data *data)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (data->cmd[i])
	{
		if (!(ft_strchr_int(data->cmd[i], 39) == 0
				&& ft_strchr_int(data->cmd[i], 34) == 0
				&& ft_strchr_int(data->cmd[i], '$') == 0))
		{
			size += get_tokenizing_size(data->cmd[i], data->envp);
			fill_new_cmd(data, size, i);
			free(data->cmd[i]);
			data->cmd[i] = ft_strdup(data->tokenized_str);
			free(data->tokenized_str);
		}
		i++;
	}
}

int	get_tokenizing_size(char *cmd, char **envp)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
			size += get_quote_modif_size(cmd, envp, &i);
		if (cmd[i] == '$')
		{
			size += get_env_variable_size(&cmd[i + 1], envp);
			while (cmd[i] && check_char(cmd[i]) >= 0)
				i++;
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

void	fill_new_cmd(t_data *data, int size, int cmd_index)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	data->tokenized_str = malloc((size + 1) * sizeof(char));
	while (data->cmd[cmd_index][i])
	{
		if (data->cmd[cmd_index][i] == 34 || data->cmd[cmd_index][i] == 39)
			fill_tokenized_cmd_with_quotes(data, &i, &j, cmd_index);
		else if (data->cmd[cmd_index][i] == '$')
		{
			get_env_variable(data, &i, &j, cmd_index);
			while (data->cmd[cmd_index][i]
				&& check_char(data->cmd[cmd_index][i]) >= 0)
				i++;
		}
		else
		{
			data->tokenized_str[j] = data->cmd[cmd_index][i];
			j++;
			i++;
		}
	}
	data->tokenized_str[j] = '\0';
}
