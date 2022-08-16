/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:40:35 by pirabaud          #+#    #+#             */
/*   Updated: 2022/04/11 11:50:25 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	index;
	size_t	len_dest;
	size_t	len_src;

	index = 0;
	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	if (size < len_dest)
		return (size + len_src);
	while (src[index] && (len_dest + index) < (size - 1))
	{
		dest[len_dest + index] = src[index];
		++index;
	}
	dest[len_dest + index] = '\0';
	return (len_dest + len_src);
}
