/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:20:55 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/14 09:52:02 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (data->parsing[i])
	{
		if (ft_strcmp(data->parsing[i], "|") == 0)
		{
			ft_pipe(data);
			return (1);
		}
		++i;
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
	return (0);
}
