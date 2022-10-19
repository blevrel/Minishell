/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:28:29 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 13:18:18 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_rdest(char *rdest, const char *rsrc, size_t n)
{
	size_t		index;

	index = 0;
	while (index < n)
	{
		rdest[index] = rsrc[index];
		index++;
	}
	return (rdest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*rsrc;
	char		*rdest;

	rdest = dest;
	rsrc = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			--n;
			rdest[n] = rsrc[n];
		}
		rdest[n] = rsrc[n];
		return (dest);
	}
	rdest = fill_rdest(rdest, rsrc, n);
	return (dest);
}
