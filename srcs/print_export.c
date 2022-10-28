/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:58:28 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/28 09:10:34 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_line(const char *str)
{
	int	j;
	int	count_quote;

	j = 0;
	count_quote = 0;
	while (str[j])
	{
		if (str[j - 1] == '=' && count_quote == 0)
		{
			count_quote = 1;
			ft_putchar('\"');
		}
		ft_putchar(str[j]);
		++j;
	}
	if (str[j - 1] == '=')
		ft_putstr("\"\"");
	else if (count_quote == 1)
		ft_putchar('\"');
}

void	print_export(char	**print)
{
	int	i;

	i = 0;
	while (print[i] != NULL)
	{
		ft_printf("declare -x ");
		print_line(print[i]);
		ft_putchar('\n');
		++i;
	}
}
