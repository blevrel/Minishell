/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:09:36 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 21:17:02 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_join_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (1);
		++i;
	}
	return (0);
}

char	*join_value_env(char *str, int line, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while(str[i] && str[i] != '=')
		++i;
	if (str[i] == '=')
		++i;
	tmp = ft_strjoin(env[line], &str[i]);
	free(env[line]);
	env[line] = NULL;
	return (tmp);
}

void	replace_value(char *str, int line, t_data *data)
{
	if (check_join_value(str) == 1)
	{
		data->envp[line] = join_value_env(str, line, data->envp);
		return ;
	}
	free(data->envp[line]);
	data->envp[line] = ft_strdup(str);
}

int	search_new_env(char **cmd, char **env)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strchr_int(cmd[i], '=') > 0 && search_env(cmd[i], env) == -1)
			++res;
		++i;
	}
	return (res);
}

char	**new_env_export(char **cmd, char **env)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = malloc((search_new_env(cmd, env)
				+ size_tab(env) + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = size_tab(env);
	j = 1;
	new_env = cpy_tab(new_env, env);
	free_double_tab(env);
	while (cmd[j] != NULL)
	{
		if (ft_strchr_int(cmd[j], '=') > 0 && search_env(cmd[j], new_env) == -1
			&& check_value(cmd[j]) == 0)
			new_env[i++] = ft_strdup(cmd[j]);
		++j;
	}
	new_env[i] = NULL;
	return (new_env);
}
