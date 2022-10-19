/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:57:51 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/19 21:49:33 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_closing_quotes(char *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i])
	{
		if (ft_strchr_int(&s[i], '"') == 0 && ft_strchr_int(&s[i], '\'') == 0)
			return (0);
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
			{
				i++;
				if (!s[i])
					return (0);
			}
		}
		else if (s[i])
			i++;
	}
	return (1);
}
