/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:28:32 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 14:13:19 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlenloc(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		++i;
	}
	return (i);
}

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (ft_strlenloc(s) <= start)
	{
		str = malloc(sizeof(char));
		str[i] = '\0';
		return (str);
	}
	else if (diffls(s, start) >= len)
		str = malloc((len + 1) * sizeof(char));
	else
		str = malloc((diffls(s, start) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (ft_strlenloc(s) <= start)
	{
		str[i] = '\0';
		return (str);
	}
	while (s[start] && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
