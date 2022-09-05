/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:20:55 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/26 16:15:49 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		if (ft_strcmp(data->cmd[i], "|") == 0)
		{
			ft_pipe(data);
			return (1);
		}
		++i;
	}
	return (0);
}

int	check_double_red(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		if (ft_strcmp(data->cmd[i], "<<") == 0)
		{
			here_doc(data);
			return (1);
		}
		if (ft_strcmp(data->cmd[i], ">>") == 0)
		{
			append(data);
			return (1);
		}
		++i;
	}
	return (0);
}

int	check_redirection(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		if (ft_strcmp(data->cmd[i], "<") == 0)
		{
			entry_red(data);
			return (1);
		}
		if (ft_strcmp(data->cmd[i], ">") == 0)
		{
			exit_red(data);
			return (1);
		}
		i++;
	}		
	return (0);
}
