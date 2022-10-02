/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:55:38 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/29 14:55:44 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	get_env_variable(t_data *data, int *i, int *j, int cm_i)
{
	char	*to_find;
	int		envp_i;
	int		envp_char_i;

	(*i)++;
	envp_char_i = 0;
	to_find = isolate_env_var(&data->parsing[cm_i][*i]);
	if (!to_find)
		return ;
	while (data->parsing[cm_i][*i] && check_char(data->parsing[cm_i][*i]) == 0)
		(*i)++;
	envp_i = check_env_var(to_find, data->envp);
	if (envp_i > 0)
	{
		while (data->envp[envp_i][envp_char_i] != '=')
			envp_char_i++;
		fill_env_variable(data, j, &data->envp[envp_i][envp_char_i + 1]);
		if (data->parsing[cm_i][*i] == '$')
			get_env_variable(data, i, j, cm_i);
		return ;
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
	int		j;
	char	*to_find;

	i = 0;
	j = 0;
	if (!cmd[i] || check_char(cmd[i] != 0))
		return (NULL);
	while (cmd[i] && check_char(cmd[i]) == 0)
		i++;
	to_find = ft_calloc(sizeof(char), (i + 2));
	if (!to_find)
		return (NULL);
	i = 0;
	if (cmd[i] == '$')
		i++;
	while (cmd[i] && check_char(cmd[i]) == 0)
	{
		to_find[j] = cmd[i];
		i++;
		j++;
	}
	to_find[j] = '=';
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
