/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:08:26 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/13 14:05:49 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	list_syntax_errors(char *str)
{
	if (ft_strncmp(str, ">>>", 3) == 0)
		return (1);
	if (ft_strncmp(str, "<<<", 3) == 0)
		return (1);
	if (ft_strncmp(str, "||", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	return (0);
}

char	*parse_arg_for_syntax_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (list_syntax_errors(&str[i]) == 1)
			return (NULL);
		if (list_syntax_errors(&str[i]) == 2)
		{
			i += 2;
			if (next_non_spc_char(i, str) == 0)
				return (NULL);
		}
		if (str[i] == '|')
		{
			i++;
			if (next_non_spc_char(i, str) == 0)
				return (NULL);
		}
		if (check_char(&str[i]) < 0)
			i = move_index_after_quote(str, i, str[i]);
		i++;
	}
	return (str);
}

char	*check_syntax_error(char *str)
{
	char	*res;

	if (check_closing_quotes(str) == 1)
	{
		ft_printf("Missing_quote\n");
		return (NULL);
	}
	res = parse_arg_for_syntax_error(str);
	return (res);
}
