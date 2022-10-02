/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:42:14 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/27 16:35:04 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_strnchr_int(const char *s, int c, int size)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	while (s[index] && index < size)
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

int	size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	**cpy_tab(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	return (dest);
}
