/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:21 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/25 15:34:05 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	modify_quotes(t_data *data, int i)
{
	int	len;

	len = ft_strlen(data->cmd[i]);
	modify_single_quotes(data->cmd[i], len);
	modify_double_quotes(data->cmd[i], len);
}

void	modify_single_quotes(char *cmd, int len)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_calloc(sizeof(char), (len - 1));
	if (result == NULL)
		return ;
	if (cmd[i] == 39 && cmd[len - 1] == 39)
	{
		while (i < len - 2)
		{
			result[i] = cmd[i + 1];
			i++;
		}
		free(cmd);
		cmd = ft_strdup(result);
		free(result);
	}
}

void	modify_double_quotes(char *cmd, int len)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_calloc(sizeof(char), (len - 1));
	if (result == NULL)
		return ;
	if (cmd[i] == 34 && cmd[len - 1] == 34)
	{
		while (i < len - 2)
		{
			result[i] = cmd[i + 1];
			i++;
		}
		free(cmd);
		cmd = ft_strdup(result);
		free(result);
	}
}
