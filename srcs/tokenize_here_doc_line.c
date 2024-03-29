/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_here_doc_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:29:54 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/11 15:27:49 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	size_heredoc(char *line, t_data *data, char *limiter)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (ft_strcmp(limiter, line) == 0)
		return (ft_strlen(line));
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '$'
			&& check_char(&line[i + 1]) >= 0)
		{
			res += get_env_variable_size(&line[i], data->envp, data);
			i = move_indextoenv(line, i);
		}
		else
		{
			res++;
			i++;
		}
	}
	return (res);
}
