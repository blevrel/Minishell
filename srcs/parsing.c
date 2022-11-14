/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:41:36 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/14 11:40:38 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_quote(char *arg, int *i)
{
	int	quote;
	int	count;
	int	inside;

	count = 0;
	inside = 1;
	if (check_char(&arg[*i]) > -1 || arg[*i] == '|')
		return (0);
	quote = arg[*i];
	(*i)++;
	while (arg[*i] && (inside || (!inside && check_char(&arg[*i]) <= 0)))
	{
		if (arg[*i] == quote && inside)
			inside = 0;
		else if (!inside && check_char(&arg[*i]) < 0)
		{
			quote = arg[*i];
			inside = 1;
		}
		count++;
		(*i)++;
	}
	if (count <= 0)
		return (0);
	return (1);
}

int	fill_pipe(t_data *data, char **final_tab, int *i, int *j)
{		
	int	count;
	int	cpy_i;
	int	k;

	count = 0;
	cpy_i = *i;
	k = 0;
	while (check_char(&data->arg[cpy_i]) == 3)
	{
		cpy_i++;
		count++;
	}
	final_tab[*j] = malloc((count + 1) * sizeof(char));
	if (verif_malloc_str(final_tab, *j) == 1)
		return (1);
	while (data->arg[*i] && check_char(&data->arg[*i]) == 3)
	{
		final_tab[*j][k] = data->arg[*i];
		(*i)++;
		k++;
	}
	final_tab[*j][k] = '\0';
	(*j)++;
	return (0);
}

char	**alloc_final_tab(t_data *data)
{
	char	**final_tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	final_tab = ft_calloc((nb_arg(data->arg) + 1), sizeof (char *));
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
			final_tab[*j] = alloc_first_arg(data->arg, i);
			if (final_tab[*j] == NULL)
				return (NULL);
			(*j)++;
			if (ft_strcmp(final_tab[*j - 1], "export") == 0)
				if (fill_after_export(final_tab, data->arg, i, j) == 1)
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
	return (final_tab);
}
