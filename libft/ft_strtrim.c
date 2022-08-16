/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:33:38 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/16 14:13:44 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlenloc(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

static int	check_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}

static int	nb_set(char const *s, char const *set)
{
	int	i;
	int	res;
	int	lens;

	lens = ft_strlenloc(s);
	i = 0;
	res = 0;
	while (check_set(s[i], set) == 1 && s[i])
	{
		++i;
		++res;
	}
	if (i != lens)
	{
		while (check_set(s[lens - 1], set) == 1)
		{
			--lens;
			++res;
		}
	}
	return (res);
}

static int	check_end(char const *s, char const *set)
{
	int	i;
	int	res;

	i = ft_strlenloc(s);
	res = 0;
	while (check_set(s[i - 1], set) == 1 && i > 0)
	{
		++res;
		--i;
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		end;
	int		j;

	j = 0;
	i = 0;
	end = check_end(s1, set);
	str = malloc((ft_strlenloc(s1) - nb_set(s1, set) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i] && check_set(s1[i], set) == 1)
		++i;
	while (s1[i] && i < (ft_strlenloc(s1) - end))
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
