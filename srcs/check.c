/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:20:55 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/09 16:06:34 by pirabaud         ###   ########.fr       */
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
