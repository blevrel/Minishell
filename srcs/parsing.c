/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:41:36 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/11 14:00:40 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_quote(char *arg, int *i)
{
	int	quote;
	int	count;

	count = 0;
	if (check_char(&arg[*i]) > -1 || arg[*i] == '|')
		return (0);
	quote = arg[*i];
	(*i)++;
	while (arg[*i] && arg[*i] != quote)
	{
		(*i)++;
		count++;
	}
	if (arg[*i])
		(*i)++;
	if (count <= 0)
		return (0);
	return (1);
}

int	fill_pipe(t_data *data, char **final_tab, int *i, int *j)
{		
	final_tab[*j] = malloc((count_size_arg(&data->arg[*i], 3) + 1)
			* sizeof(char));
	if (verif_malloc_str(final_tab, *j) == 1)
		return (1);
	fill_arg(final_tab[(*j)++], data->arg, i, 3);
	return (0);
}

char	**alloc_final_tab(t_data *data)
{
	char	**final_tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	final_tab = malloc((nb_arg(data->arg) + 1) * sizeof (char *));
	if (verif_malloc_arr(final_tab) == 1)
		return (NULL);
	final_tab = fill_final_tab(final_tab, data, &i, &j);
	return (final_tab);
}

char	**fill_final_tab(char **final_tab, t_data *data, int *i, int *j)
{
	while (data->arg[*i])
	{
		if (check_size_first_arg(data->arg, *i) != 0)
		{
			final_tab[(*j)++] = alloc_first_arg(data->arg, i);
			if (final_tab[*j - 1] == NULL)
				return (NULL);
		}
		if (fill_until_pipe(final_tab, data->arg, i, j) == 1)
			return (NULL);
		if (data->arg[*i] == '|')
		{
			if (fill_pipe(data, final_tab, i, j) == 1)
				return (NULL);
		}
	}
	final_tab[*j] = NULL;
	return (final_tab);
}
