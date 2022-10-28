/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 08:18:00 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/28 09:50:51 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_heredoc_null(char **final_tab, char *arg, int *line)
{
	if (check_here_doc_null(arg) == 1)
	{
		(*line)++;
		final_tab[*line] = malloc(sizeof(char));
		if (verif_malloc_str(final_tab, *line) == 1)
			return (1);
		return (0);
	}
	return (0);
}

int	check_fill_heredoc_null(char **final_tab, char *arg, int *i, int *j)
{
	if (*j == 0)
		return (0);
	if (ft_strcmp(final_tab[*j - 1], "<<") == 0)
	{
		if (ft_strncmp(&arg[*i], "\"\"", 2) == 0
			|| ft_strncmp(&arg[*i], "\'\'", 2) == 0)
		{
			*i += 2;
			if (check_char(&arg[*i]) != 0 || arg[*i] == 0)
			{
				final_tab[*j][0] = '\0';
				(*j)++;
				return (1);
			}
			else
				return (0);
		}
		return (0);
	}
	return (0);
}
