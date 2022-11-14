/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arr_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:40:20 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/14 11:15:06 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	fill_with_quotes(char **final_tab, char *arg, int *i, int *j)
{
	int	k;
	int	quote;
	int	inside;

	inside = 1;
	if (check_char(&arg[*i]) > -1 || arg[*i] == '|')
		return ;
	k = ft_strlen(final_tab[*j]);
	if (check_fill_heredoc_null(final_tab, arg, i, j) == 1)
		return ;
	quote = arg[*i];
	final_tab[*j][k++] = arg[(*i)++];
	while (arg[*i] && (inside || (!inside && check_char(&arg[*i]) <= 0)))
	{
		if (arg[*i] == quote && inside)
			inside = 0;
		else if (!inside && check_char(&arg[*i]) < 0)
		{
			quote = arg[*i];
			inside = 1;
		}
		final_tab[*j][k++] = arg[(*i)++];
	}
	(*j)++;
}

void	fill_arg(char **final_tab, char *arg, int *i, int *j)
{
	int	k;

	k = 0;
	if (check_char(&arg[*i]) == 2)
	{
		while (arg[*i] && check_char(&arg[*i]) == 2)
		{
			final_tab[*j][k] = arg[*i];
			(*i)++;
			k++;
		}
		(*j)++;
		return ;
	}
	while (arg[*i] && check_char(&arg[*i]) <= 0)
	{
		if (check_char(&arg[*i]) < 0)
			fill_with_quotes(final_tab, arg, i, j);
		else
		{
			ft_fill_char_and_increment(final_tab[*j], arg, i, &k);
			if (!arg[*i] || check_char(&arg[*i]) > 0)
				(*j)++;
		}
	}
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
			fill_arg(final_tab, arg, i, j);
		if (arg[*i] && check_char(&arg[*i]) == 0)
			fill_arg(final_tab, arg, i, j);
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
		res[*j] = arg[*i];
		(*j)++;
		if (check_char(&arg[*i]) < 0)
		{
			quote = arg[*i];
			while (arg[++(*i)] != quote)
			{
				res[*j] = arg[*i];
				(*j)++;
			}
			res[*j] = arg[*i];
			(*j)++;
		}
		(*i)++;
	}
	res[*j] = '\0';
	return (res);
}
