/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:03:14 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 14:19:30 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		index;
	char	*occ;

	index = 0;
	occ = (char *)s;
	while (s[index])
	{
		if (s[index] == (unsigned char)c)
			return (&occ[index]);
		index++;
	}
	if (c == 0)
		return (&occ[index]);
	return (0);
}
