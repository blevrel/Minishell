/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_here_doc_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:29:54 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/28 11:12:18 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	size_here_doc_line(char *line, t_data *data)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '$'
			&& check_char(&line[i + 1]) >= 0)
		{
			res += get_env_variable_size(&line[i], data->envp, data);
			move_indextoenv(line, &i);
		}
		else
		{
			res++;
			i++;
		}
	}
	return (res);
}
