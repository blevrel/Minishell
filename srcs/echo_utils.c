/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:25:34 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/17 10:13:04 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*tokenize_env_var(char *full_arg, char *res, t_data *data, int *i)
{
	char	*find;
	int		line;
	int		len;

	line = 0;
	(*i)++;
	if (full_arg[*i] == '?')
		return (fill_returnvalue(data, res, i));
	find = isolate_env_var(&full_arg[*i]);
	len = size_env(find);
	while (full_arg[*i] && ft_isalnum(full_arg[*i]) != 0 && full_arg[*i] != '$')
		(*i)++;
	if (len == -1)
	{
		free(find);
		return (res);
	}
	while (data->envp[line] && ft_strncmp(data->envp[line], find, len + 1) != 0)
		line++;
	free(find);
	if (!data->envp[line])
		return (res);
	res = ft_strjoin_no_malloc(res, &data->envp[line][len + 1]);
	return (res);
}

char	*replace_env_in_quotes(char *full_arg, char *res, t_data *data, int *i)
{
	int	quote;
	int	j;

	quote = full_arg[*i];
	j = ft_strlen(res);
	if (check_char(&full_arg[*i + 1]) > 1 && full_arg[*i + 2] == quote)
	{
		res[j++] = quote;
		res[j + 1] = quote;
	}
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
	if (full_arg[*i])
		(*i)++;
	return (res);
}

char	*tokenize_full_arg(char *arg, t_data *data)
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
			res = replace_env_in_quotes(arg, res, data, &i);
		else if (arg[i] == '$' && (ft_isalnum(arg[i + 1]) == 8
				|| arg[i + 1] == '?'))
			res = tokenize_env_var(arg, res, data, &i);
		else
		{
			j = ft_strlen(res);
			ft_fill_char_and_increment(res, arg, &i, &j);
		}
	}
	return (res);
}
