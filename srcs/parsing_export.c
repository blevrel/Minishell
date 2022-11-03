/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 08:44:36 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/03 16:32:34 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_exp(char *arg, int *i)
{
	int	res;

	res = 0;
	while (arg[*i] && (check_char(&arg[*i]) <= 0))
		res += go_to_first_arg(arg, i);
	return (res);
}

int	count_size_exp(char *arg)
{
	int	i;
	int	res;
	int	quote;

	i = 0;
	res = 0;
	quote = 0;
	while (arg[i] && check_char(&arg[i]) == 1)
		i++;
	while (arg[i] && (check_char(&arg[i]) <= 0))
	{
		if (check_char(&arg[i]) < 0)
		{
			quote = arg[i];
			while (arg[++i] != quote)
				res++;
		}
		i++;
		res++;
	}
	return (res);
}

char	*alloc_export(char *arg, int *i)
{
	char	*res;
	int		j;

	j = 0;
	res = malloc((count_size_exp(&arg[*i]) + 1) * sizeof(char));
	if (verif_malloc_str(&res, 0) == 1)
		return (NULL);
	while (arg[*i] && check_char(&arg[*i]) == 1)
		(*i)++;
	res = fill_exp(arg, res, i, &j);
	return (res);
}

int	fill_after_export(char **final_tab, char *arg, int *i, int *j)
{
	while (arg[*i] && check_char(&arg[*i]) == 1)
			(*i)++;
	while (arg[*i] && (check_char(&arg[*i]) <= 0))
	{
		final_tab[*j] = alloc_export(arg, i);
		if (final_tab[*j] == NULL)
		{
			free_double_tab(final_tab);
			return (1);
		}
		(*j)++;
	}
	return (0);
}

char	*fill_exp(char *arg, char *res, int *i, int *j)
{
	int	quote;

	quote = 0;
	while (arg[*i] && (check_char(&arg[*i]) <= 0))
	{
		res[(*j)++] = arg[*i];
		if (check_char(&arg[*i]) < 0)
		{
			quote = arg[*i];
			while (arg[++(*i)] != quote)
			{
				res[*j] = arg[*i];
				(*j)++;
			}
			res[(*j)++] = arg[*i];
		}
		(*i)++;
	}
	res[*j] = '\0';
	return (res);
}
