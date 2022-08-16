/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:21:47 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 14:14:07 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_last(char *s, int i, int c)
{
	while (s[i])
	{
		++i;
		if (s[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*occ;

	occ = (char *)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c && check_last(occ, i, c) == 0)
			return (&occ[i]);
		++i;
	}
	if (c == 0)
		return (&occ[i]);
	return (0);
}
