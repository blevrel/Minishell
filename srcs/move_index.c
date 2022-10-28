/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:43:38 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/28 13:48:03 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_indextoenv(char *str, int *i)
{
	if (!str)
		return ;
	if (str[*i] == '$')
		(*i)++;
	while (str[*i])
	{
		if (str[*i] == '$' || check_char(&str[*i]) != 0)
			return ;
		(*i)++;
	}
}

int	move_index_after_quote(char *str, int i)
{
	int	quote;

	if (!str)
		return (0);
	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i])
		i++;
	return (i);
}
