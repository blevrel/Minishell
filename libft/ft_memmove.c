/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:28:29 by pirabaud          #+#    #+#             */
/*   Updated: 2022/07/27 10:40:53 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*rsrc;
	char		*rdest;
	size_t		index;

	index = -1;
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
	while (++index < n)
		rdest[index] = rsrc[index];
	return (dest);
}
