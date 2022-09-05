/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:26:43 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/27 14:32:08 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	parsing_arg(t_data *data)
{
	int	i;
	int	tab_size;

	i = 0;
	tab_size = get_cmd_tab_size(data->arg);
	data->cmd = ft_calloc(sizeof(char *), tab_size + 1);
	while (i < tab_size)
	{
		allocate_cmd(data->arg, &data->cmd[i], tab_size);
		if (!data->cmd[i])
			return ;
		i++;
	}
}
