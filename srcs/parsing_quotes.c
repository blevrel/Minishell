/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:57:51 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/23 18:08:49 by blevrel          ###   ########.fr       */
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
	return (1);
}


