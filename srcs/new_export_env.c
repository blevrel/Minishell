/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:09:36 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/17 10:40:22 by blevrel          ###   ########.fr       */
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
	char	*tmp2;

	tmp2 = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	if (str[i] == '=')
		++i;
	if (ft_strchr_int(env[line], '=') == 0)
	{
		tmp = ft_strjoin(env[line], "=");
		tmp2 = ft_strjoin(tmp, &str[i]);
		free(tmp);
		free(env[line]);
		return (tmp2);
	}
	tmp = ft_strjoin(env[line], &str[i]);
	free(env[line]);
	env[line] = NULL;
	return (tmp);
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
	if (verif_malloc_arr(new_env) == 1)
		return (NULL);
	i = size_tab(env);
	j = 1;
	new_env = cpy_tab(new_env, env);
	free_double_tab(env);
	while (cmd[j] != NULL)
	{
		if (ft_strchr_int(cmd[j], '=') > 0 && search_env(cmd[j], new_env) == -1
			&& check_value(cmd[j]) == 0)
			new_env[i++] = new_value_env(cmd[j]);
		++j;
	}
	new_env[i] = NULL;
	return (new_env);
}
