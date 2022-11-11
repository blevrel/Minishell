/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:35:09 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/10 09:36:58 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	reset_pipe_index_if_needed(char *full_arg)
{
	int	i;

	i = 0;
	while (full_arg[i])
	{
		if (full_arg[i] == '|')
			return (1);
		if (check_char(&full_arg[i]) < 0)
			i = move_index_after_quote(full_arg, i + 1);
		else
			i++;
	}
	return (0);
}

int	reset_index_if_needed(char *full_arg, int i, int j)
{
	int	prev_char;
	int	next_char;

	while (full_arg[i + j])
	{
		prev_char = check_char(&full_arg[i + j - 1]);
		next_char = check_char(&full_arg[i + j + 1]);
		if (check_char(&full_arg[i + j]) > 1 && prev_char == next_char)
			return (1);
		j++;
	}
	return (0);
}

