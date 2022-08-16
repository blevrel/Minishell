/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 08:56:13 by pirabaud          #+#    #+#             */
/*   Updated: 2022/05/10 10:43:52 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_adress(va_list param)
{
	int						count;
	unsigned long long int	p;

	count = 0;
	p = (unsigned long long int)va_arg(param, void *);
	if (p != 0)
		count = count + ft_putstr("0x");
	count = count + putnbr_adress(p, "0123456789abcdef");
	return (count);
}

int	check_print(char c, va_list param)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(param, int));
	if (c == 's')
		count = count + ft_putstr(va_arg(param, char *));
	if (c == 'd' || c == 'i')
		count = count + ft_putnbr(va_arg(param, int));
	if (c == 'x')
		count += putnbr_hex(va_arg(param, unsigned int), "0123456789abcdef");
	if (c == 'X')
		count += putnbr_hex(va_arg(param, unsigned int), "0123456789ABCDEF");
	if (c == '%')
		count += ft_putchar('%');
	if (c == 'p')
		count = count + print_adress(param);
	if (c == 'u')
		count = count + putnbr_unsigned(va_arg(param, unsigned int));
	return (count);
}
