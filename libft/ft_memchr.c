/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:57:18 by pirabaud          #+#    #+#             */
/*   Updated: 2022/07/27 10:24:14 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*res;
	size_t			i;

	res = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (res[i] == (unsigned char) c)
			return (&res[i]);
		++i;
	}
	if (c == 0 && n != 0)
		return (&res[i]);
	return (0);
}
