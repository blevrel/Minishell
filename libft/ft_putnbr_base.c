/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:53:24 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 16:56:44 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(int nb, int base, char *str)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		count = count + ft_putnbr_base(nb / base, base, str);
		count += ft_putchar(str[nb % base]);
	}
	else if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
		count = count + ft_putnbr_base(nb, base, str);
	}
	else if (nb >= base)
	{
		count = count + ft_putnbr_base(nb / base, base, str);
		count += ft_putchar(str[nb % base]);
	}
	else
	{
		count += ft_putchar(str[nb % base]);
	}
	return (count);
}
