/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:53 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/27 16:33:28 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_print_end(char *str)
{
	if (ft_strcmp(str, ">") == 0 || (ft_strcmp(str, "<") == 0
			|| ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0))
		return (1);
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "&&") == 0)
		return (1);
	return (0);
}

void	echo(t_cmd *data)
{
	int	i;

	if (ft_strcmp(data->cmd[1], "-n") == 0)
	{
		i = 2;
		while (data->cmd != NULL && check_print_end(data->cmd[i]) != 1)
			ft_printf("%s", data->cmd[i++]);
	}
	else
	{
		i = 1;
		while (data->cmd != NULL && check_print_end(data->cmd[i]) != 1)
			ft_printf("%s", data->cmd[i++]);
		ft_printf("\n");
	}
}
