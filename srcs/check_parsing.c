/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:15:26 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/25 17:22:26 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	last_non_spc_char(int i, char *str)
{
	char	c;

	c = str[i + 1];
	if (i < 0)
		return ('>');
	while (i >= 0)
	{
		if (check_char(str[i]) != 1)
			return (str[i]);
		i--;
	}
	if (check_char(c) == 2)
		return ('>');
	return (' ');
}

char	last_diff_and_non_spc_char(int i, char *str)
{
	char	c;

	c = str[i + 1];
	if (i < 0)
		return ('>');
	while (i >= 0)
	{
		if (check_char(str[i]) != 1 && str[i] != c)
			return (str[i]);
		i--;
	}
	if (check_char(c) == 2)
		return ('>');
	return (' ');
}

char	next_non_spc_char(int i, char *str)
{
	while (str[i])
	{
		if (check_char(str[i]) != 1)
			return (str[i]);
		i++;
	}
	return (' ');
}

int	check_char(char c)
{
	if (c == 34)
		return (-2);
	if (c == 39)
		return (-3);
	if (c == '<' || c == '>' || c == '|')
		return (2);
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	if (c == '$')
		return (-1);
	return (0);
}
