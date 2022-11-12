/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:03:02 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/12 16:46:57 by pirabaud         ###   ########.fr       */
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

	i = 0;
	while (i < size)
	{
		waitpid(son[i], &status, 0);
		i++;
	}
	i = 1;
	data->return_value = get_return_value(status);
	if (data->return_value == 131)
		ft_printf("Quit (core dumped)\n");
	else if (data->return_value == 130)
		ft_printf("\n");
}
