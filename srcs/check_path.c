/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:54 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 11:40:26 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*init_res(char *env, char *cmd)
{
	int		i;
	char	*tmp;
	char	*res;
	char	**path;

	i = 0;
	path = ft_split(env, ':');
	tmp = ft_strjoin(path[i], "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	while (access(res, F_OK) != 0 && path[i] != NULL)
	{
		i++;
		free(res);
		tmp = ft_strjoin(path[i], "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	if (path[i] == NULL)
	{
		free_double_tab(path);
		free(res);
		return(NULL);
	}
	free_double_tab(path);
	return (res);
}

int	check_cmd_no_print(char *cmd)
{
	if (check_command(cmd) == 1)
		return (0);
	if (!(ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0))
		return (1);
	else if (cmd && access(cmd, F_OK) != 0)
		return (1);
	else if (cmd && access(cmd, X_OK) != 0)
		return (1);
	return (0);
}

int	check_valid_cmd_for_static_reset(t_data *data, char *cmd)
{
	char	*res;
	int		line;

	line = 0;
	while (data->envp[line] != NULL
		&& ft_memcmp(data->envp[line], "PATH", 4) != 0)
		line++;
	if (data->envp[line] == NULL)
		return (1);
	res = init_res(data->envp[line], cmd);
	if (res && access(res, F_OK) == 0 && access(res, X_OK) == 0)
	{
		free(res);
		return (0);
	}
	free(res);
	if (check_cmd_no_print(cmd) == 1)
		return (1);
	return (0);
}

int	check_cmd(char *cmd, t_data *data)
{
	if (check_command(cmd) == 1)
		return (0);
	if (!(ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0))
	{
		ft_print_error("%s : command not found\n", cmd);
		data->return_value = 127;
		return (1);
	}
	else if (cmd && access(cmd, F_OK) != 0)
	{
		ft_print_error("minishell: %s: No such file or directory\n", cmd);
		data->return_value = 127;
		return (1);
	}
	else if (cmd && access(cmd, X_OK) != 0)
	{
		ft_print_error("minishell: %s: Permission denied\n", cmd);
		data->return_value = 126;
		return (1);
	}
	else if (cmd && opendir(cmd) != NULL)
	{
		ft_print_error("minishell: %s: Is a directory\n", cmd);
		data->return_value = 126;
		return (1);
	}
	return (0);
}

char	*check_path(char *cmd, t_data *data)
{
	char	*res;
	int		line;

	line = 0;
	if (cmd == NULL)
		return (NULL);
	if (check_command(cmd) == 1)
		return (ft_strdup(cmd));
	while (data->envp[line] != NULL
		&& ft_memcmp(data->envp[line], "PATH", 4) != 0)
		line++;
	if (data->envp[line] == NULL || ft_strcmp(cmd, ".") == 0
		|| ft_strcmp(cmd, "..") == 0)
	{
		ft_print_error("%s : Command not found\n", cmd);
		data->return_value = 127;
		return (NULL);
	}
		res = init_res(data->envp[line], cmd);
	if (res && access(res, F_OK) == 0 && access(res, X_OK) == 0)
		return (res);
	free(res);
	if (check_cmd(cmd, data) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}
