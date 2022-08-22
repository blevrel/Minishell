/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:42:14 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/22 14:20:34 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_arg(char **cmd, char c)
{
	int		i;
	char	**res;

	i = 0;
	while (cmd[i] != NULL && cmd[i][0] != c)
		++i;
	res = malloc(i * sizeof(char *));
	i = 0;
	while (cmd[i] != NULL && cmd[i][0] != c)
	{
		res[i] = ft_strdup(cmd[i]);
		++i;
	}
	res[i] = NULL;
	return (res);
}

int	ft_strchr_int(const char *s, int c)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	while (s[index])
	{
		if (s[index] == (unsigned char)c)
			count++;
		index++;
	}
	return (count);
}

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
