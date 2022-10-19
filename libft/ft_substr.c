/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:28:32 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 14:15:08 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	diffls(char const *s, unsigned int start)
{
	size_t	i;

	i = 0;
	while (s[start])
	{
		i++;
		start++;
	}
	return (i);
}

static char	*fill_str(char *res, char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[start] && i < len)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (ft_strlen(s) <= start)
	{
		res = malloc(sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	else if (diffls(s, start) >= len)
		res = malloc((len + 1) * sizeof(char));
	else
		res = malloc((diffls(s, start) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		res[0] = '\0';
		return (res);
	}
	return (fill_str(res, s, start, len));
}
