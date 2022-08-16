/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:00:19 by pirabaud          #+#    #+#             */
/*   Updated: 2022/07/27 10:01:39 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_gnl(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}
