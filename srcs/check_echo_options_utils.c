/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_echo_options_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:03:37 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/18 04:13:33 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_option_format_in_quotes(char *full_arg, int *j, char quote)
{
	(*j)++;
	while (full_arg[*j] != quote)
	{
		if (full_arg[*j] != 'n')
			return (1);
		(*j)++;
	}
	(*j)++;
	return (0);
}

int	check_option_format(char *full_arg, char *option)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (full_arg[j] != option[i])
		j++;
	j++;
	while (full_arg[j] == 'n' || check_char(&full_arg[j]) < 0)
	{
		if (check_char(&full_arg[j]) < 0
			&& check_closing_quotes(&full_arg[j]) == 0)
		{
			if (check_option_format_in_quotes(full_arg, &j, full_arg[j]) == 1)
				return (1);
		}
		else if (full_arg[j] == 'n' || check_char(&full_arg[j]) < 0)
			j++;
	}
	if (!full_arg[j] || check_char(&full_arg[j]) == 1)
		return (0);
	else
		return (1);
}
