/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:16:34 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/20 18:15:30 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_quotes(t_data *data, int i)
{
	if (ft_strchr_int(data->cmd[i], 34) % 2 == 1)
	{
		printf("Missing double quote\n");
		return (-1);
	}
	if (ft_strchr_int(data->cmd[i], 39) % 2 == 1)
	{
		printf("Missing single quote\n");
		return (-1);
	}
	if (ft_strchr_int(data->cmd[i], 34) == 0 && ft_strchr_int(data->cmd[i],
			39) == 0)
		return (0);
	modify_quotes(data, i);
	return (1);
}

int	check_double_red(t_data data)
{
	int	i;

	i = 0;
	while (data.cmd[i])
	{
		if (ft_strcmp(data.cmd[i], "<<") == 0)
		{
			here_doc(data);
			return (1);
		}
		if (ft_strcmp(data.cmd[i], ">>") == 0)
		{
			append(data);
			return (1);
		}
		++i;
	}
	return (0);
}

int	check_redirection(t_data data)
{
	int	i;

	i = 0;
	while (data.cmd[i])
	{
		if (ft_strcmp(data.cmd[i], "<") == 0)
		{
			entry_red(data);
			return (1);
		}
		if (ft_strcmp(data.cmd[i], ">") == 0)
		{
			exit_red(data);
			return (1);
		}
		i++;
	}		
	return (0);
}
