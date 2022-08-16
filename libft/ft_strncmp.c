/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:02:10 by pirabaud          #+#    #+#             */
/*   Updated: 2022/03/30 17:52:01 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s2[i] && i < n)
	{
		if ((unsigned char )s1[i] != (unsigned char )s2[i])
			return ((unsigned char )s1[i] - (unsigned char) s2[i]);
		++i;
	}
	if (i == n)
		--i;
	return ((unsigned char )s1[i] - ((unsigned char ) s2[i]));
}
