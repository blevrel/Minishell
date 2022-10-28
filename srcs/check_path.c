/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:54 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/28 09:51:39 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_res(char *path, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(path, "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

int	find_path_line(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL && ft_memcmp(env[i], "PATH", 4) != 0)
		i++;
	return (i);
}

int	check_cmd(char *cmd, t_data *data)
{
	if (check_command(cmd) == 1)
		return (0);
	if (!(ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0))
	{
		printf("%s : command not found\n", cmd);
		data->return_value = 127;
		return (1);
	}
	else if (access(cmd, F_OK) != 0)
	{
		printf("minishell: %s: no such file or directory\n", cmd);
		data->return_value = 127;
		return (1);
	}
	else if (access(cmd, X_OK) != 0)
	{
		printf("minishell: %s: permission denied\n", cmd);
		data->return_value = 126;
		return (1);
	}
	return (0);
}

char	*check_path(char *cmd, char **env, t_data *data)
{
	int		i;
	char	*res;
	char	**path;

	i = find_path_line(env);
	if (env[i] == NULL )
		return (NULL);
	path = ft_split(env[i], ':');
	i = 0;
	res = init_res(path[i], cmd);
	i++;
	while (access(res, F_OK) != 0 && path[i] != NULL)
	{
		free(res);
		res = init_res(path[i], cmd);
		i++;
	}
	free_double_tab(path);
	if (access(res, X_OK) == 0 && access(res, X_OK) == 0)
		return (res);
	free(res);
	if (check_cmd(cmd, data) == 0)
		return (ft_strdup(cmd));
	else
		return (NULL);
}
