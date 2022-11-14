/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_first_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:28:07 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/13 09:27:15 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**remove_first_arg(t_data *data)
{
	int		i;
	char	**new_parsing_tab;

	i = 0;
	new_parsing_tab = ft_calloc(sizeof(char *), size_tab(data->parsing));
	if (verif_malloc_arr(new_parsing_tab) == 1)
		return (NULL);
	while (data->parsing[i + 1])
	{
		new_parsing_tab[i] = ft_strdup(data->parsing[i + 1]);
		i++;
	}
	free_double_tab(data->parsing);
	data->arg = remove_first_arg_in_full_arg(data);
	return (new_parsing_tab);
}

char	*remove_first_arg_in_full_arg(t_data *data)
{
	char	*new_arg;
	int		i;

	i = 0;
	while (check_char(&data->arg[i]) == 1)
		i++;
	if (check_char(&data->arg[i]) < 0)
		i = move_index_after_quote(data->arg, i + 1);
	while (check_char(&data->arg[i]) == 0)
		i++;
	while (check_char(&data->arg[i]) == 1)
		i++;
	new_arg = ft_strdup(&data->arg[i]);
	free(data->arg);
	return (new_arg);
}

void	remove_arg_if_needed(t_data *data)
{
	int		i;
	char	**save_parsing;

	i = 0;
	save_parsing = malloc((size_tab(data->parsing) + 1) * sizeof(char *));
	if (verif_malloc_arr(save_parsing) == 1)
	{
		clean_data(data, 0);
		exit (1);
	}
	while (data->parsing[i])
	{
		save_parsing[i] = ft_strdup(data->parsing[i]);
		i++;
	}
	save_parsing[i] = NULL;
	i = 0;
	while (!save_parsing[i][0])
	{
		data->parsing = remove_first_arg(data);
		i++;
	}
	free_double_tab(save_parsing);
}
