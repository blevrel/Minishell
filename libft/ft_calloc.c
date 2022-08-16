/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:01:27 by pirabaud          #+#    #+#             */
/*   Updated: 2022/07/27 10:28:18 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	i;

	i = 0;
	if ((float) nmemb * size >= (float) 18446744073709551615UL)
		return (NULL);
	res = malloc(nmemb * size);
	if (res == NULL)
		return (0);
	while (i < (nmemb * size))
	{
		res[i] = 0;
		++i;
	}
	return (res);
}
