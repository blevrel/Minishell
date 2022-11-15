/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 08:56:13 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/15 09:39:49 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_error(char c)
{
	return(write(2, &c, 1));
}

int	ft_putstr_error(char *str)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	if (str == NULL)
	{
		count = ft_putstr_error("(null)");
		return (count);
	}
	while (str[i])
	{
		ft_putchar_error(str[i]);
		i++;
		count++;
	}
	return (count);
}

int	ft_putnbr_error(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		count = count + ft_putnbr_error(nb / 10);
		count += ft_putchar_error('8');
	}
	else if (nb < 0)
	{
		count += ft_putchar_error('-');
		nb = -nb;
		count = count + ft_putnbr_error(nb);
	}
	else if (nb >= 10)
	{
		count = count + ft_putnbr_error(nb / 10);
		count += ft_putchar_error(nb % 10 + '0');
	}
	else
		count += ft_putchar_error(nb % 10 + '0');
	return (count);
}
int	print_adress_error(va_list param)
{
	int						count;
	unsigned long long int	p;

	count = 0;
	p = (unsigned long long int)va_arg(param, void *);
	if (p != 0)
		count = count + ft_putstr_error("0x");
	count = count + putnbr_adress_error(p, "0123456789abcdef");
	return (count);
}

int	check_print_error(char c, va_list param)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_error(va_arg(param, int));
	if (c == 's')
		count = count + ft_putstr_error(va_arg(param, char *));
	if (c == 'd' || c == 'i')
		count = count + ft_putnbr_error(va_arg(param, int));
	if (c == 'x')
		count += putnbr_hex(va_arg(param, unsigned int), "0123456789abcdef");
	if (c == 'X')
		count += putnbr_hex(va_arg(param, unsigned int), "0123456789ABCDEF");
	if (c == '%')
		count += ft_putchar_error('%');
	if (c == 'p')
		count = count + print_adress_error(param);
	if (c == 'u')
		count = count + putnbr_unsigned(va_arg(param, unsigned int));
	return (count);
}
