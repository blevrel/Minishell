/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:43:38 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/03 12:59:33 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_indextoenv(char *str, int i)
{
	if (!str)
		return (i);
	if (str[i] == '$')
		i++;
	while (str[i])
	{
		if (str[i] == '$' || ft_isalnum(str[i]) == 0)
			return (i);
		i++;
	}
	return (i);
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
