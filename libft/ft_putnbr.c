/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:53:24 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 16:54:22 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		count = count + ft_putnbr(nb / 10);
		count += ft_putchar('8');
	}
	else if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
		count = count + ft_putnbr(nb);
	}
	else if (nb >= 10)
	{
		count = count + ft_putnbr(nb / 10);
		count += ft_putchar(nb % 10 + '0');
	}
	else
		count += ft_putchar(nb % 10 + '0');
	return (count);
}
