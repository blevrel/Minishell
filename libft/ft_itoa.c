/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:30:00 by pirabaud          #+#    #+#             */
/*   Updated: 2022/07/27 10:31:43 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lgstr(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		++count;
		if (n == -2147483648)
		{
			n = n / 10;
			++count;
		}
		n = -n;
	}
	while (n >= 10)
	{
		++count;
		n = n / 10;
	}
	return (count);
}

static char	*swaploc(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = 0;
	while (str[j])
		++j;
	--j;
	while (i < j)
	{
		if (str[i] == '-')
			++i;
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		--j;
		++i;
	}
	return (str);
}

static char	*init_str(char *str, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		str[i++] = '0';
	while (n > 0 || n < 0)
	{
		if (n < 0)
		{
			str[i++] = '-';
			if (n == -2147483648)
			{
				str[i++] = '8';
				n = n / 10;
			}
			n = n * -1;
		}
		str[i] = n % 10 + '0';
		++i;
		n = n / 10;
	}
	str[i] = '\0';
	str = swaploc(str);
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		leng;

	leng = lgstr(n);
	str = malloc((leng + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = init_str(str, n);
	return (str);
}
