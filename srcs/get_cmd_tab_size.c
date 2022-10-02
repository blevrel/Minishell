/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_tab_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:55:07 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/02 14:03:22 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_cmd_tab_size(char *arg)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ')
		i++;
	while (arg[i])
	{
		if (check_char(arg[i]) < -1)
			cmd_tab_size_quotes(&i, arg, arg[i]);
		if (check_char(arg[i]) == 1 && (check_char(arg[i + 1]) == 0
				|| check_char(arg[i + 1]) < -1)
			&& check_char(last_non_spc_char(i, arg)) <= 1 && arg[i + 1])
			count++;
		get_size_with_sep_and_env_var(arg, &i, &count);
		if ((check_char(arg[i]) >= -1 || check_closing_quotes(&arg[i]) == 1
				|| (ft_strchr_int(&arg[i], 34) == 0
					&& ft_strchr_int(&arg[i], 39) == 0)) && arg[i])
			i++;
	}
	return (count);
}

void	get_size_with_sep_and_env_var(char *arg, int *i, int *count)
{
	if (check_char(arg[*i]) == 2 && check_char(arg[*i + 1]) <= 1)
	{
		if (arg[*i + 1] && check_char(next_non_spc_char(*i + 1, arg)) <= 1
			&& (check_char(last_non_spc_char(*i - 1, arg)) <= 1
				|| check_char(last_diff_and_non_spc_char(*i - 1, arg)) <= 1))
			(*count)++;
		(*count)++;
	}
	if (check_only_space_before_index(*i, arg) == 0 && check_char(arg[*i]) == -1
		&& check_char(arg[*i - 1]) != 2
		&& ft_strnchr_int(arg, ' ', *i) != 0)
		get_size_with_env_var(arg, i, count);
	if (check_only_space_before_index(*i, arg) == 1
		&& check_char(arg[*i]) == -1)
		(*i)++;
}

void	get_size_with_env_var(char *arg, int *i, int *count)
{
	int	quote;

	(*count)++;
	(*i)++;
	while (arg[*i] && check_char(arg[*i]) < 1 && arg[*i] != '$')
	{
		if (arg[*i] == 34 || arg[*i] == 39)
		{
			(*count)++;
			quote = arg[*i];
			(*i)++;
			while (arg[*i] != quote)
				(*i)++;
			return ;
		}
		else
			(*i)++;
	}
	(*i)--;
}
