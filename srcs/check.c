/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:16:34 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/19 14:26:10 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_double_red(t_data data)
{
	int	i;

	i = 0;
	while (data.cmd[i] != NULL)
	{
		if (ft_strcmp(data.cmd[i], "<<") == 0)
		{
			here_doc(data);
			return (1);
		}
		/*if (ft_strcmp(data.cmd[i], ">>") == 0)
		{
			append(data);
			return (1);
		}*/
		++i;
	}
	return (0);
}

int	check_redirection(t_data data)
{
	int	i;

	i = 0;
	while (data.cmd[i] != NULL)
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
