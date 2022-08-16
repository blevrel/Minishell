/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:34:05 by pirabaud          #+#    #+#             */
/*   Updated: 2022/03/30 13:35:17 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	index;

	index = 0;
	if (size != 0)
	{
		while (size - 1 > 0 && src[index])
		{
			dst[index] = src[index];
			++index;
			--size;
		}
		dst[index] = 0;
	}
	while (src[index])
	{
		++index;
	}
	return (index);
}
