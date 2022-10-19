/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arr_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:40:20 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/17 14:24:20 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	fill_arg(char *final_tab, char *arg, int *i, int value)
{
	int	j;

	j = 0;
	while (arg[*i] && check_char(&arg[*i]) == value)
	{
		final_tab[j] = arg[*i];
		(*i)++;
		j++;
	}
	final_tab[j] = '\0';
}

void	fill_with_quotes(char **final_tab, char *arg, int *i, int *j)
{
	int	k;
	int	quote;

	k = 0;
	if (check_char(&arg[*i]) > -1 || arg[*i] == '|')
		return ;
	if (ft_strncmp(&arg[*i], "\"\"", 2) == 0)
	{
		*i += 2;
		return ;
	}
	quote = arg[*i];
	final_tab[*j][k++] = arg[*i];
	(*i)++;
	while (arg[*i] && arg[*i] != quote)
	{
		final_tab[*j][k] = arg[*i];
		k++;
		(*i)++;
	}
	final_tab[*j][k] = arg[*i];
	k++;
	final_tab[*j][k] = '\0';
	(*i)++;
	(*j)++;
}

int	fill_until_pipe(char **final_tab, char *arg, int *i, int *j)
{
	if (alloc_until_pipe(final_tab, arg, *i, *j) == 1)
		return (1);
	while (arg[*i] && arg[*i] != '|')
	{
		while (arg[*i] && check_char(&arg[*i]) == 1)
				(*i)++;
		if (arg[*i] && check_char(&arg[*i]) == 2)
		{
			fill_arg(final_tab[*j], arg, i, 2);
			(*j)++;
		}
		if (arg[*i] && check_char(&arg[*i]) == 0 && arg[*i] != '|')
		{
			fill_arg(final_tab[*j], arg, i, 0);
			(*j)++;
		}
		fill_with_quotes(final_tab, arg, i, j);
	}
	return (0);
}

char	*alloc_first_arg(char *arg, int *i)
{
	char	*res;
	int		j;

	j = 0;
	res = malloc((count_size_first_arg(&arg[*i]) + 1) * sizeof(char));
	if (verif_malloc_str(&res, 0) == 1)
		return (NULL);
	while (arg[*i] && check_char(&arg[*i]) == 1)
		(*i)++;
	res = fill_first_arg(arg, res, i, &j);
	return (res);
}

char	*fill_first_arg(char *arg, char *res, int *i, int *j)
{
	int	quote;

	quote = 0;
	while (arg[*i] && check_char(&arg[*i]) <= 0)
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
