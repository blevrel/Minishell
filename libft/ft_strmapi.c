/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:36:46 by pirabaud          #+#    #+#             */
/*   Updated: 2022/07/27 10:28:47 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strlenloc(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	str = malloc((strlenloc((char *)s) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = (char)s[i];
		str[i] = (*f)(i, str[i]);
		++i;
	}
	str[i] = '\0';
	return (str);
}
