/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:30:51 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 16:50:28 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	char	*cbig;

	i = 0;
	cbig = (char *) big;
	if (little[i] == '\0')
		return (cbig);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i] == little[j] && big && i < len)
		{
			++j;
			++i;
			if (little[j] == '\0')
				return (&cbig[i - j]);
		}
		i = i - j;
		++i;
	}
	return (0);
}
