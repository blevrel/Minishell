/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 08:44:02 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/15 14:32:54 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putnbr_hex_error(unsigned int nb, char *str)
{
	int	count;

	count = 0;
	if (nb >= 16)
	{
		count = count + putnbr_hex_error(nb / 16, str);
		ft_putchar_error(str[nb % 16]);
		++count;
	}
	else
	{
		ft_putchar_error(str[nb % 16]);
		++count;
	}
	return (count);
}

int	putnbr_adress_error(unsigned long long int nb, char *str)
{
	int	count;

	count = 0;
	if (nb == 0)
	{
		ft_putstr_error("(nil)");
		return (5);
	}
	if (nb >= 16)
	{
		count = count + putnbr_adress_error(nb / 16, str);
		ft_putchar_error(str[nb % 16]);
		++count;
	}
	else
	{
		ft_putchar_error(str[nb % 16]);
		++count;
	}
	return (count);
}

int	putnbr_unsigned_error(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
	{
		count = count + putnbr_unsigned_error(nb / 10);
		ft_putchar_error((nb % 10) + '0');
		++count;
	}
	else
	{
		ft_putchar_error(nb + '0');
		++count;
	}
	return (count);
}

int	ft_print_error(const char *format, ...)
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
			count = count + check_print_error(format[i], param);
			++i;
		}
		else
		{
			write(2, &format[i], 1);
			++count;
			++i;
		}
	}
	va_end(param);
	return (count);
}
