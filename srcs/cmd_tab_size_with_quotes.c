/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_size_with_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:55:54 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/24 15:16:45 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	cmd_tab_size_quotes(int *i, char *arg)
{
	int	count;

	count = 0;
	if (check_char(arg[*i - 1]) == 0)
		count++;
	*i += 1;
	while (check_char(arg[*i]) != -1)
	{
		if (!arg[*i + 1])
			break ;
		*i += 1;
	}
	if (check_char(arg[*i + 1]) <= 0 && arg[*i + 1])
		count++;
	return (count);
}
