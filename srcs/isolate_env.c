/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:08:17 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/13 11:17:18 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*fill_isolated_env_var(char *to_find, char *cmd, int i, int j)
{
	if (cmd[i] == '?')
	{
		to_find[j] = '?';
		j++;
	}
	else
	{
		while (cmd[i] && ft_isalnum(cmd[i]) == 8)
		{
			to_find[j] = cmd[i];
			i++;
			j++;
		}
	}
	to_find[j] = '=';
	to_find[j + 1] = '\0';
	return (to_find);
}

char	*isolate_env_var(char *cmd)
{
	int		i;
	int		j;
	char	*to_find;

	i = 0;
	j = 0;
	if (!cmd[i] || check_char(&cmd[i]) > 0)
		return (NULL);
	if (cmd[i] == '$' || cmd[i] == '\"')
		i++;
	if (cmd[i] == '?')
		j++;
	else
		while (cmd[i + j] && ft_isalnum(cmd[i + j]) == 8)
			j++;
	to_find = malloc(sizeof(char) * (j + 2));
	if (verif_malloc_str(&to_find, 0) == 1)
		return (NULL);
	j = 0;
	to_find = fill_isolated_env_var(to_find, cmd, i, j);
	return (to_find);
}
