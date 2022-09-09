/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:55:38 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/09 11:35:08 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	get_env_variable(t_data *data, int *i, int *j, int cmd_i)
{
	char	*to_find;
	int		envp_i;
	int		envp_char_i;

	(*i)++;
	envp_i = 0;
	envp_char_i = 0;
	to_find = isolate_env_var(&data->cmd[cmd_i][*i]);
	while (data->cmd[cmd_i][*i] && check_char(data->cmd[cmd_i][*i]) == 0)
		(*i)++;
	while (data->envp[envp_i])
	{
		if (ft_strncmp(data->envp[envp_i], to_find, ft_strlen(to_find)) == 0)
		{
			while (data->envp[envp_i][envp_char_i] != '=')
				envp_char_i++;
			fill_env_variable(data, j, &data->envp[envp_i][envp_char_i + 1]);
			return ;
		}
		envp_i++;
	}
}

void	fill_env_variable(t_data *data, int *j, char *env_var_line)
{
	int	i;

	i = 0;
	while (env_var_line[i])
	{
		data->tokenized_str[*j] = env_var_line[i];
		(*j)++;
		i++;
	}
}

char	*isolate_env_var(char *cmd)
{
	int		i;
	char	*to_find;

	i = 0;
	while (cmd[i] && check_char(cmd[i]) == 0)
		i++;
	to_find = ft_calloc(sizeof(char), (i + 1));
	i = 0;
	while (cmd[i] && check_char(cmd[i]) == 0)
	{
		to_find[i] = cmd[i];
		i++;
	}
	return (to_find);
}

int	get_env_variable_size(char *cmd, char **envp)
{
	int		i;
	int		j;
	char	*to_find;

	i = 0;
	j = 0;
	to_find = isolate_env_var(cmd);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], to_find, ft_strlen(to_find)) == 0)
		{
			while (envp[i][j] != '=')
				j++;
			return (ft_strlen(&envp[i][j + 1]));
		}
		i++;
	}
	return (0);
}
