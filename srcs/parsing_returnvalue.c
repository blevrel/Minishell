/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_returnvalue.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:23:49 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/03 16:49:25 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*fill_returnvalue(t_data *data, char *res, int *i)
{
	char	*value;

	value = ft_itoa(data->return_value);
	if (!res)
	{
		ft_putstr_fd("itoa failed", 2);
		return (NULL);
	}
	res = join_gnl(res, value);
	if (!res)
		ft_putstr_fd("join_gnl failed", 2);
	free(value);
	(*i)++;
	return (res);
}

int	replace_valuereturn(char *dest, int *j, t_data *data)
{	
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	value = ft_itoa(data->return_value);
	if (value == NULL)
	{
		ft_putstr_fd("Malloc failed", 2);
		return (1);
	}
	while (value[i])
	{
		dest[*j] = value[i];
		(*j)++;
		++i;
	}
	free(value);
	return (0);
}
