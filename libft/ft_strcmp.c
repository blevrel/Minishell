/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:52:56 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/16 09:56:16 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*cast_s1;
	unsigned char	*cast_s2;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	cast_s1 = (unsigned char *)s1;
	cast_s2 = (unsigned char *)s2;
	while (cast_s1[i] == cast_s2[i] && cast_s2[i])
		i++;
	return (cast_s1[i] - cast_s2[i]);
}
