/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:26:30 by pirabaud          #+#    #+#             */
/*   Updated: 2022/07/27 10:32:47 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		index;
	char		*rdest;
	const char	*rsrc;

	index = 0;
	rdest = dest;
	rsrc = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (index < n)
	{
		rdest[index] = rsrc[index];
		++index;
	}
	return (rdest);
}
