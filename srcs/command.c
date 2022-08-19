/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:58 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/18 13:13:34 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_cmd(t_data data)
{
	char *path;
	
	path = check_path(data.cmd[0], data.envp);
	pid_t son;

	son = fork();
	if (son == 0)
		execve(path, data.cmd, data.envp);
	waitpid(son, NULL, 0);
}
