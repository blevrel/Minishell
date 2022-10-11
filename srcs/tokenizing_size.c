/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:08:32 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/10 14:03:30 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	size_in_quote(char *str, int *i, int quote, char **env)
{
	int	count;

	count = 0;
	while (str[*i] != quote)
	{
		if (quote == 34 && str[*i] == '$' && str[*i + 1] != '$')
		{
			count += get_env_variable_size(&str[*i], env);
			move_indextoenv(str, i);
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

int	size_tokenize(char *src, char **env)
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
			res += size_in_quote(src, &i, quote, env);
		}
		else if (src[i] == '$' && src[i + 1] != '$')
		{
			res += get_env_variable_size(&src[i], env);
			move_indextoenv(src, &i);
		}
		else
		{
			res++;
			i++;
		}
	}
	return (res);
}
