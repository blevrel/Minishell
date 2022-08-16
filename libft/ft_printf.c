/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 08:44:02 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 14:23:51 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putnbr_hex(unsigned int nb, char *str)
{
	int	count;

	count = 0;
	if (nb >= 16)
	{
		count = count + putnbr_hex(nb / 16, str);
		ft_putchar(str[nb % 16]);
		++count;
	}
	else
	{
		ft_putchar(str[nb % 16]);
		++count;
	}
	return (count);
}

int	putnbr_adress(unsigned long long int nb, char *str)
{
	int	count;

	count = 0;
	if (nb == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	if (nb >= 16)
	{
		count = count + putnbr_adress(nb / 16, str);
		ft_putchar(str[nb % 16]);
		++count;
	}
	else
	{
		ft_putchar(str[nb % 16]);
		++count;
	}
	return (count);
}

int	putnbr_unsigned(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
	{
		count = count + putnbr_unsigned(nb / 10);
		ft_putchar((nb % 10) + '0');
		++count;
	}
	else
	{
		ft_putchar(nb + '0');
		++count;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	param;
	int		i;
	int		count;

	count = 0;
	i = 0;
	va_start(param, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			++i;
			count = count + check_print(format[i], param);
			++i;
		}
		else
		{
			write(1, &format[i], 1);
			++count;
			++i;
		}
	}
	va_end(param);
	return (count);
}
