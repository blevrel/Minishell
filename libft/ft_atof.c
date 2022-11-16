/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:24:27 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 14:31:26 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_atof(const char *nptr)
{
	int		i;
	float		res;
	int		sign;

	i = 0;
	res = 0;
	sign = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		++i;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			++sign;
		++i;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10.0 + (nptr[i] - '0');
		++i;
	}
	if (sign == 1)
		res = res * -1.0;
	return (res);
}
