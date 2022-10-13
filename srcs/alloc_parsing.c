/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:34:33 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/11 13:44:51 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_size_first_arg(char *arg, int i)
{
	int	count;
	int	quote;

	count = 0;
	quote = 0;
	while (arg[i] && check_char(&arg[i]) == 1)
		i++;
	while (arg[i] && check_char(&arg[i]) <= 0)
	{
		if (check_char(&arg[i]) < 0)
		{
			quote = arg[i];
			while (arg[++i] != quote)
				count++;
		}
		i++;
		count++;
	}
	if (count == 0)
		return (0);
	return (count);
}

int	alloc_with_quotes(char **final_tab, char *arg, int *i, int *j)
{
	int	quote;
	int	count;

	count = 1;
	if (check_char(&arg[*i]) > -1 || arg[*i] == '|')
		return (0);
	quote = arg[*i];
	(*i)++;
	while (arg[*i] && arg[*i] != quote)
	{
		(*i)++;
		count++;
	}
	if (count != 1)
	{
		final_tab[*j] = malloc((count + 2) * sizeof(char));
		if (verif_malloc_str(final_tab, *j) == 1)
			return (1);
		(*j)++;
	}
	if (arg[*i])
		(*i)++;
	return (0);
}

int	alloc_until_pipe(char **final_tab, char *arg, int i, int j)
{
	while (arg[i] && arg[i] != '|')
	{
		while (arg[i] && check_char(&arg[i]) == 1)
				i++;
		if (arg[i] && check_char(&arg[i]) == 2)
		{
			final_tab[j] = malloc((count_size_arg(&arg[i], 2) + 1)
					* sizeof(char));
			if (verif_malloc_str(final_tab, j++) == 1)
				return (1);
			while (check_char(&arg[i]) == 2)
				i++;
		}
		if (arg[i] && check_char(&arg[i]) == 0 && arg[i] != '|')
		{
			final_tab[j] = malloc((count_size_arg(&arg[i], 0) + 1)
					* sizeof(char));
			if (verif_malloc_str(final_tab, j++) == 1)
				return (1);
			while (arg[i] && check_char(&arg[i]) == 0)
				i++;
		}
		alloc_with_quotes(final_tab, arg, &i, &j);
	}
	return (0);
}