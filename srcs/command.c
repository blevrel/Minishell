/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:58 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/22 14:21:22 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*cmd_not_found(char *cmd)
{
	if (ft_strchr_int(cmd, '/') != 0)
		printf("%s: No such file or directory\n", cmd);
	else
		printf("%s: command not found\n", cmd);
	return (NULL);
}

void	simple_cmd(t_data *data)
{
	char	*path;
	pid_t	son;

	path = check_path(data->cmd[0], data->envp);
	if (!path)
		return ;
	son = fork();
	if (son == 0)
		execve(path, data->cmd, data->envp);
	free(path);
	waitpid(son, NULL, 0);
}
