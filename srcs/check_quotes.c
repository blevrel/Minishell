/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:57:51 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/08 17:40:17 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_closing_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (ft_strchr_int(&str[i], '"') == 0
			&& ft_strchr_int(&str[i], '\'') == 0)
			return (0);
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
			{
				i++;
				if (!str[i])
					return (0);
			}
		}
		else if (str[i])
			i++;
	}
	return (1);
}
