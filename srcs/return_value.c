/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:03:02 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 16:53:11 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_return_value(int status)
{
	if (WIFEXITED(status) == 1)
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) == 1)
		return (128 + WTERMSIG(status));
	return (1);
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
	int	trigger;

	i = 0;
	trigger = 0;
	while (i <= size)
	{
		waitpid(son[i], &status, 0);
		if (i == 0 && size > 1)
		{
			data->return_value = get_return_value(status);
			if (data->return_value == 130)
				trigger = 1;
		}
		i++;
	}
	data->return_value = get_return_value(status);
	if (data->return_value == 131)
		ft_printf("Quit (core dumped)\n");
	else if (data->return_value == 130 || trigger == 1)
		ft_printf("\n");
}
