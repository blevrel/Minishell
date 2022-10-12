/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:09:41 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/10 13:46:43 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	size_env(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != '=')
			++i;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

char	*isolate_env_var(char *cmd)
{
	int		i;
	int		j;
	char	*to_find;

	i = 0;
	j = 0;
	if (!cmd[i] || check_char(&cmd[i]) > 0)
		return (NULL);
	if (cmd[i] == '$' || cmd[i] == '\"')
		i++;
	while (cmd[i + j] && check_char(&cmd[i + j]) == 0 && cmd[i + j] != '$')
		j++;
	to_find = malloc(sizeof(char) * (j + 2));
	if (!to_find)
		return (NULL);
	j = 0;
	while (cmd[i] && check_char(&cmd[i]) == 0 && cmd[i] != '$')
	{
		to_find[j] = cmd[i];
		i++;
		j++;
	}
	to_find[j] = '=';
	to_find[j + 1] = '\0';
	return (to_find);
}

int	get_env_variable_size(char *cmd, char **envp)
{
	int		i;
	int		res;
	int		len_env;
	char	*value;

	i = 0;
	value = isolate_env_var(cmd);
	len_env = size_env(value);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], value, len_env + 1) == 0 && len_env != -1)
		{
			res = ft_strlen(&envp[i][len_env + 1]);
			return (res);
		}
		i++;
	}
	return (0);
}

void	fill_env(char *res, char *str, char **env, int *j)
{
	int		i;
	int		line;
	int		len_env;
	char	*value;

	line = 0;
	i = 1;
	value = isolate_env_var(str);
	len_env = size_env(value);
	if (len_env == -1)
		return ;
	while (env[line] && ft_strncmp(env[line], value, len_env + 1) != 0)
		++line;
	if (!env[line])
		return ;
	while (env[line][len_env + i])
	{
		res[*j] = env[line][len_env + i];
		i++;
		(*j)++;
	}
	res[*j] = '\0';
}
