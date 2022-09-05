/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_with_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:01:28 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/02 15:37:46 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	parsing_with_space(char *arg, int *i, int *not_first_arg, int *trigger)
{
	*not_first_arg = 1;
	*trigger = 1;
	if (!arg[*i + 1])
		return (reset_statics(i, not_first_arg, 0));
	return (0);
}

void	fill_cmd_space(char *arg, int *i, int *trigger)
{
	*trigger = 1;
	if (!arg[*i + 1])
		*i = 0;
}
