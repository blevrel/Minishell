/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:03:02 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/03 17:07:31 by blevrel          ###   ########.fr       */
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

int	size_return_value(t_data *data)
{
	int	res;
	int	tmp;

	res = 1;
	tmp = data->return_value;
	while (tmp >= 10)
	{
		tmp = tmp / 10;
		++res;
	}
	return (res);
}

void	return_value(int *son, t_data *data, int size)
{
	int	i;
	int	status;

	i = 0;
	while (i <= size)
	{
		waitpid(son[i], &status, 0);
		i++;
	}
	i = 0;
	while (i < size)
	{
		free(data->pipexfd[i]);
		data->pipexfd[i] = 0;
		i++;
	}
	free(data->pipexfd);
	data->pipexfd = 0;
	data->return_value = replace_vreturn(status);
	if (data->return_value == 131)
		ft_printf("Quit (core dumped)\n");
	else if (data->return_value == 130)
		ft_printf("\n");
}
