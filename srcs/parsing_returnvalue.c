/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_returnvalue.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:23:49 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/09 11:03:43 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*fill_returnvalue(t_data *data, char *res, int *i)
{
	char	*value;

	value = ft_itoa(data->return_value);
	if (!res)
	{
		ft_putstr_fd("Error\n", 2);
		return (NULL);
	}
	//res = join_return_value(res, value, ft_strlen_var(data->arg, data));
	res = ft_strjoin_no_malloc(res, value);
	if (verif_malloc_str(&res, 0) == 1)
		return (NULL);
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
