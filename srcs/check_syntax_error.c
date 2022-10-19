/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:08:26 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/19 04:07:38 by blevrel          ###   ########.fr       */
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
	if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str, ">", 1) == 0)
		return (3);
	if (ft_strncmp(str, "<", 1) == 0)
		return (3);
	if (ft_strncmp(str, "|", 1) == 0)
		return (3);
	return (0);
}

int	move_index_after_space(char *str, int i, char c)
{
	while (str[i] == c)
		i++;
	while (check_char(&str[i]) == 1)
		i++;
	return (i);
}

char	*parse_arg_for_syntax_error(char *str)
{
	int		i;
	char	save_char;

	i = 0;
	while (str[i])
	{
		if (list_syntax_errors(&str[i]) == 1)
			return (NULL);
		if (list_syntax_errors(&str[i]) > 1)
		{
			save_char = str[i];
			i = move_index_after_space(str, i, str[i]);
			if (!str[i] || (save_char != '|' && check_char(&str[i]) > 1))
				return (NULL);
		}
		if (check_char(&str[i]) < 0)
			i = move_index_after_quote(str, i + 1, str[i]);
		i++;
	}
	return (str);
}

char	*check_syntax_error(char *str)
{
	char	*res;

	if (next_non_spc_char(0, str) == '|')
	{
		ft_printf("Syntax error\n");
		return (NULL);
	}
	if (check_closing_quotes(str) == 1)
	{
		ft_printf("Missing_quote\n");
		return (NULL);
	}
	res = parse_arg_for_syntax_error(str);
	if (res == NULL)
		ft_printf("Syntax error\n");
	return (res);
}
