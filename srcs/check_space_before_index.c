/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space_before_index.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:35:34 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/30 19:02:59 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_only_space_before_index(int limit, char *str)
{
	int	i;

	i = 0;
	while (check_char(str[i]) == 1 && i < limit)
		i++;
	if (i == limit)
		return (1);
	return (0);
}

int	check_space_before_index(int limit, char *str)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		if (check_char(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
