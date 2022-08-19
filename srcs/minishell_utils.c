/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:42:14 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/19 14:27:41 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **check_arg(char **cmd, char c)
{
	int	i;
	char **res;

	i = 0;
	while(cmd[i] != NULL && cmd[i][0] != c)
		++i;
	res = malloc(i * sizeof(char *));
	i = 0;
	while(cmd[i] != NULL && cmd[i][0] != c)
	{
		res[i] = ft_strdup(cmd[i]);
		++i;
	}
	res[i] = NULL;
	return (res);
}
