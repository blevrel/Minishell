/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:00:19 by pirabaud          #+#    #+#             */
/*   Updated: 2022/07/27 11:47:17 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = -1;
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
	if (s2 != NULL)
	{
		while (s2[++j])
			res[i + j] = s2[j];
	}
	res[i + j] = '\0';
	return (res);
}
