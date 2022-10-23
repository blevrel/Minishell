/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:09:41 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 13:56:09 by pirabaud         ###   ########.fr       */
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

int	size_return_value(t_data *data)
{
	int	res;
	int	tmp;
	
	res = 1;
	tmp = data->return_value;
	while (tmp >= 10)
	{
		tmp = tmp/10;
		++res;
	}
	return (res);
}

int	get_env_variable_size(char *cmd, char **envp, t_data *data)
{
	int		i;
	int		res;
	int		len_env;
	char	*value;

	i = 0;
	value = isolate_env_var(cmd);
	len_env = size_env(value);
	if (ft_strcmp(value, "?=") == 0)
	{
		res = size_return_value(data);
		return (res);
	}
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

char	*ft_cpy_env(char *dest, int *i, char *src)
{	
	int	j;

	j = 0;
	while (src[j])
	{
		dest[*i] = src[j];
		(*i)++;
		j++;
	}
	dest[*i] = '\0';
	return (dest);
}

int	replace_valuereturn(char *dest, int *j, t_data *data)
{	
	char *value;
	int	i;

	i = 0;
	value = NULL;
	value = ft_itoa(data->return_value);
	if (value == NULL)
	{
		ft_putstr_fd("Malloc failed", 2);
		return (1);
	}
	while (value[i])
	{
		dest[*j] = value[i];
		(*j)++;
		++i;
	}
	free(value);
	return (0);
}

int	fill_env(char *res, char *str, t_data *data, int *j)
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
		return (2);
	if (ft_strcmp(value, "?=") == 0)
	{
		if (replace_valuereturn(res, j, data) == 1)
			return (1);
		return (0);
	}
	while (data->envp[line] && ft_strncmp(data->envp[line], value, len_env + 1) != 0)
		++line;
	if (!data->envp[line])
		return (2);
	res = ft_cpy_env(res, j, &data->envp[line][len_env + i]);
	return (0);
}
