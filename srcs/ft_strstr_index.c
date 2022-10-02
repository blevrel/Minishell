/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:30:51 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/28 17:04:38 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strstr_index(char *big, char *little)
{
	static int	i = 0;
	int			j;

	if (!little[0])
		return (index_forward(big, &i, 1));
	while (big[i])
	{
		j = 0;
		while (big[i] == little[j])
		{
			++j;
			++i;
			while (big[i] == 34 || big[i] == 39)
				i++;
			if (!little[j])
			{
				if (!big[i])
					return (reset_statics(&i, &j, i, 1));
				return (reset_statics(&i, &j, i, 3));
			}
		}
		i -= j;
		++i;
	}
	return (index_forward(big, &i, 0));
}

int	index_forward(char *big, int *original_index, int trigger)
{
	static int	i = 0;
	int			temp;

	temp = 0;
	if (trigger == 1)
	{
		i = *original_index;
		return (env_var_not_found(original_index, &i, big));
	}
	*original_index = i;
	while (big[i])
	{
		temp = index_after_env_var(big, &i, &temp, original_index);
		if (temp != -1)
			return (temp);
	}
	temp = i;
	if (!big[i])
		*original_index = 0;
	i = 0;
	return (temp);
}

int	index_after_env_var(char *big, int *i, int *temp, int *original_index)
{
	if (big[*i] == 34 || big[*i] == 39)
	{
		index_after_quote_with_env_var(big, i);
		*temp = *i;
		if (ft_strchr_int(&big[*i], '$') == 0)
			return (reset_statics(i, original_index, *temp, 2));
		return (reset_statics(i, original_index, *temp, 0));
	}
	else if (big[*i] == '$')
	{
		(*i)++;
		while ((big[*i] && check_char(big[*i]) == 0))
		(*i)++;
		*temp = *i;
		if (ft_strchr_int(&big[*i], '$') == 0)
			return (reset_statics(i, original_index, *temp, 2));
		return (reset_statics(i, original_index, *temp, 0));
	}
	(*i)++;
	return (-1);
}

int	env_var_not_found(int *original_index, int *i, char *big)
{
	int	temp;

	temp = 0;
	while (check_char(big[*i]) == 1)
		(*i)++;
	(*i)++;
	while (big[*i] && (check_char(big[*i]) == 0
			|| (check_char(big[*i]) == 1 && ft_strchr_int(&big[*i], '$') == 0)))
		(*i)++;
	temp = *i;
	if (!big[*i])
		return (reset_statics(i, original_index, temp, 2));
	return (reset_statics(i, original_index, temp, 0));
}

void	index_after_quote_with_env_var(char *big, int *i)
{
	int	quote;

	quote = big[*i];
	(*i)++;
	while (big[*i] != quote)
		(*i)++;
	(*i)++;
}
