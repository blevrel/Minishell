/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:08:32 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/16 19:22:39 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	size_in_quote(char *str, int *i, int quote, t_data *data)
{
	int	count;

	count = 0;
	while (str[*i] != quote)
	{
		if (quote == 34 && str[*i] == '$'
			&& (ft_isalnum(str[*i + 1]) == 8 || str[*i + 1] == '?'))
		{
			count += get_env_variable_size(&str[*i], data->envp, data);
			*i = move_indextoenv(str, *i);
		}
		else
		{
			++count;
			(*i)++;
		}
	}
	(*i)++;
	return (count);
}

int	size_tab_tokenizing(t_data *data)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;
	res = 0;
	while (data->parsing[i])
	{
		if (env_not_found(data, i) == 1)
			i++;
		else
		{
			i++;
			res++;
		}
	}
	return (res);
}

int	only_quotes(char *str)
{
	int	i;
	int	quote;

	if (!str)
		return (1);
	i = 0;
	quote = str[i];
	while (str[i])
	{
		if (str[i] != quote)
			return (1);
		i++;
	}
	return (0);
}

int	env_not_found(t_data *data, int i)
{
	if (!data->parsing[i])
		return (0);
	if (size_tokenize(data->parsing[i], data->envp, data) == 0
		&& ft_strlen(data->parsing[i]) != 0 && i != 0
		&& only_quotes(data->parsing[i]) == 1)
		return (1);
	return (0);
}

int	size_tokenize(char *src, char **env, t_data *data)
{
	int	i;
	int	res;
	int	quote;

	i = 0;
	res = 0;
	while (src[i])
	{
		if (check_char(&src[i]) < 0)
		{
			quote = src[i++];
			res += size_in_quote(src, &i, quote, data);
			continue ;
		}
		else if (src[i] == '$' && src[i + 1] != '$'
			&& (ft_isalnum(src[i + 1]) == 8 || src[i + 1] == '?'))
		{
			res += get_env_variable_size(&src[i], env, data);
			i = move_indextoenv(src, i);
			continue ;
		}
		res++;
		i++;
	}
	return (res);
}
