/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:12:18 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/27 18:03:17 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
	{
		pick_correct_echo(cmd, data);
		return (1);
	}
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
	{
		pwd();
		return (1);
	}
	if (ft_strcmp(cmd->cmd[0], "env") == 0)
	{
		env(data->envp);
		return (1);
	}
	return (0);
}
