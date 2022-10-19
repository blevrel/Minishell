/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:00:19 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 14:00:29 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*fill_res(char *res, char *s, int *i, int trigger)
{
	int	j;

	j = 0;
	if (trigger == 0)
	{
		while (s[*i])
		{
			res[*i] = s[*i];
			(*i)++;
		}
	}
	else
	{
		while (s[j])
		{
			res[*i + j] = s[j];
			j++;
		}
	}
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (res == NULL)
		return (NULL);
	if (s1 != NULL)
		res = fill_res(res, (char *)s1, &i, 0);
	if (s2 != NULL)
		res = fill_res(res, (char *)s2, &i, 1);
	return (res);
}
