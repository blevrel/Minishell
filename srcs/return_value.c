/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:03:02 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/25 08:18:01 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	replace_vreturn(int value)
{
	if (value == 2)
		return (130);
	if (value == 256)
		return (1);
	return (value);
}

void	return_value(int *son, t_data *data, int size)
{
	int	i;
	int	status;

	i = 0;
	while (size >= 0)
	{
		waitpid(son[i], &status, 0);
		i++;
		--size;
	}
	data->return_value = replace_vreturn(status);
}
