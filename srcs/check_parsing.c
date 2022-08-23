/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:15:26 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/23 17:44:57 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	check_last_non_spc_char(int i, char *str)
{
	while (i > 0)
	{
		if (str[i] != ' ')
			return (str[i]);
		i--;
	}
	return (' ');
}

char	check_next_non_spc_char(int i, char *str)
{
	while (str[i])
	{
		if (str[i] != ' ')
			return (str[i]);
		i++;
	}
	return (' ');
}

int	check_char(char c)
{
	if (c == 34)
		return (-1);
	if (c == 39)
		return (-1);
	if (c == '<')
		return (2);
	if (c == '>')
		return (2);
	if (c == '|')
		return (2);
	if (c == '&')
		return (2);
	if (c == '*')
		return (2);
	if (c == ' ')
		return (1);
	return (0);
}
