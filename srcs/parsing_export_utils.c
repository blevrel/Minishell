/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:23:22 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/28 17:24:02 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export(char *str)
{
	int		i;
	int		j;
	char	*check;

	i = 0;
	j = 0;
	check = malloc(7 * sizeof(char));
	if (verif_malloc_str(&check, 0) == 1)
		return (0);
	while (str[i] && j < 6)
	{
		if (check_char(&str[i]) >= 0)
			check[j++] = str[i];
		++i;
	}
	check[j] = 0;
	if (ft_strncmp(check, "export", 6) == 0)
	{
		free(check);
		return (1);
	}
	free(check);
	return (0); 
}
