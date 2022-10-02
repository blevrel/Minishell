/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:52:40 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/29 14:54:13 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_env_var(char *str, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		++i;
	if (str[i] != '=')
		return (-1);
	while (env[j] != NULL)
	{
		if (ft_strncmp(str, env[j], i + 1) == 0)
			return (j);
		++j;
	}
	return (-1);
}
