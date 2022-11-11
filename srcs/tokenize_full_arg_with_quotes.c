/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_full_arg_with_quotes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:01:28 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/11 11:06:26 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*tokenize_in_quotes(char *full_arg, char *res, t_data *data, int *i)
{
	int	quote;
	int	j;

	quote = full_arg[*i];
	j = ft_strlen(res);
	res[j] = quote;
	j++;
	(*i)++;
	while (full_arg[*i] && full_arg[*i] != quote)
	{
		if (full_arg[*i] == '$' && quote == '\"'
			&& (ft_isalnum(full_arg[*i + 1]) == 8 || full_arg[*i + 1] == '?'))
		{
			res = tokenize_env_var(full_arg, res, data, i);
			j = ft_strlen(res);
		}
		else
			ft_fill_char_and_increment(res, full_arg, i, &j);
	}
	res[j] = quote;
	if (full_arg[*i])
		(*i)++;
	return (res);
}

char	*tokenize_full_arg_with_quotes(char *arg, t_data *data)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc((ft_strlen_var(arg, data) + 1), sizeof(char));
	if (verif_malloc_str(&res, 0) == 1)
		return (NULL);
	while (arg[i])
	{
		if (check_char(&arg[i]) < 0 && check_closing_quotes(&arg[i]) == 0)
			res = tokenize_in_quotes(arg, res, data, &i);
		else if (arg[i] == '$' && (ft_isalnum(arg[i + 1]) == 8
				|| arg[i + 1] == '?'))
			res = tokenize_env_var(arg, res, data, &i);
		else
		{
			j = ft_strlen(res);
			ft_fill_char_and_increment(res, arg, &i, &j);
		}
	}
	free(arg);
	arg = NULL;
	return (res);
}

