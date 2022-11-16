/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:20:55 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 17:28:29 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_data *data)
{
	if (check_nbpipe(data->arg) >= 1)
	{
		ft_pipe(data);
		return (1);
	}
	return (0);
}

int	check_command(char *str)
{
	if (check_redirection(str) == 1)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	return (0);
}

int	check_pipexfd(t_data *data, int i)
{
	if (pipe(data->pipexfd[i]) == -1)
	{
		ft_print_error("pipe failed\n");
		return (1);
	}
	return (0);
}

int	check_dir(char *cmd)
{
	DIR	*dir;

	if (cmd == NULL)
		return (0);
	dir = opendir(cmd);
	if (dir != NULL)
	{
		closedir(dir);
		ft_print_error("minishell: %s: Is a directory\n", cmd);
		return (1);
	}
	return (0);
}
