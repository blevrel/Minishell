/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_dp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:32:27 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 17:37:50 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**dup_dp(char **str)
{
	char **res;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while(str[i] != NULL)
		++i;
	res = malloc(i * sizeof(char *));
	while (str[j] != NULL)
	{
		res[j] = ft_strdup(str[j]);
		++j;
	}
	res[j] = NULL;
	return (res);
}
