/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:52:18 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/10 11:06:31 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	verif_malloc_arr(char **arr, int line)
{
	if (!arr)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (1);
	}
	if (!arr[line])
	{
		ft_putstr_fd("Malloc failed\n", 2);
		free_double_tab(arr);
		return (1);
	}
	return (0);
}
