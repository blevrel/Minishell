/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:43:38 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/12 16:24:50 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_indextoenv(char *str, int i)
{
	if (!str)
		return (i);
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
		return (i + 1);
	while (str[i])
	{
		if (str[i] == '$' || ft_isalnum(str[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	count_index_after_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	if (!str)
		return (0);
	quote = str[i];
	while (str[i] && str[i] == quote)
		i++;
	return (i);
}

int	move_index_after_quote(char *str, int i)
{
	int	quote;

	if (!str)
		return (0);
	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i])
		i++;
	return (i);
}

int	move_to_end_of_arg(char *str, int i)
{
	while (check_char(&str[i]) == 1)
		i++;
	while (str[i] && check_char(&str[i]) < 1)
	{
		if (check_char(&str[i]) < 0)
			i = move_index_after_quote(str, i);
		else
			i++;
	}
	return (i);
}
