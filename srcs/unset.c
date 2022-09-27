/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:19:43 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/27 13:33:21 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset(char *str, char **env)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
			i++;
	while (env[j] != NULL)
	{
		if (ft_strncmp(str, env[j], i) == 0)
			return (j);
		++j;
	}
	return (-1);
}

char	**new_tab(int i, char **src)
{
	int	j;
	int	k;
	char **new_tab;
	
	j = 0;
	k = 0;
	new_tab = malloc(size_tab(src) * sizeof(char *));
	while (src[k] != NULL)
	{
		if (j != i)
		{
			new_tab[j] = ft_strdup(src[k]);
			++j;
		}
		++k;
	}
	new_tab[j] = NULL;
	free_double_tab(src);
	return (new_tab);
}
