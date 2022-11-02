/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:52:18 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/02 10:26:37 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	verif_malloc_arr(char **arr)
{
	if (!arr)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (1);
	}
	return (0);
}

int	verif_malloc_str(char **arr, int line)
{
	if (!arr[line])
	{
		ft_putstr_fd("Malloc failed\n", 2);
		free_double_tab(arr);
		return (1);
	}
	return (0);
}

int	verif_malloc_int_arr(int **arr)
{
	if (!arr)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (1);
	}
	return (0);
}

int	verif_malloc_int(int **arr, int line)
{
	int	i;

	i = 0;
	if (!arr[line])
	{
		ft_putstr_fd("Malloc failed\n", 2);
		while (i < line)
		{
			free(arr[i]);
			i++;
		}
		return (1);
	}
	return (0);
}

int	verif_malloc_t_cmd(t_cmd *arr, int line, t_cmd **cmd_pipe)
{
	int	i;

	i = 0;
	if (!arr)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		while (i < line)
		{
			free(cmd_pipe[i]);
			i++;
		}
		return (1);
	}
	return (0);
}
