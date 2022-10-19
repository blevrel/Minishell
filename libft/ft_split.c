/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:29:55 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 13:47:14 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	nb_str(char *s, char c)
{
	int	i;
	int	nb_lett;
	int	count;

	i = 0;
	count = 0;
	if (s == NULL)
		return (0);
	if (c == '\0')
	{
		count = 1;
		return (count);
	}
	while (s[i])
	{
		nb_lett = ft_strlen_until_c(&s[i], c);
		if (nb_lett > 0)
		{
			++count;
			i = nb_lett + i;
		}
		else
			i++;
	}
	return (count);
}

static char	*strduploc(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc((ft_strlen_until_c(s, c) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != c && s[i])
	{
		str[i] = s[i];
		++i;
	}
	str[i] = '\0';
	return (str);
}

static char	**check_s(char const *s)
{
	char	**str;
	int		i;

	i = 0;
	if (s[i] == '\0')
	{
		str = malloc(sizeof(char *));
		str[0] = NULL;
	}
	else
		str = NULL;
	return (str);
}

char	**fill_split(char **split, char *s, char c, int i)
{
	int	j;

	j = 0;
	while (nb_str(s, c) > j)
	{
		while (s[i] == c)
			++i;
		split[j] = strduploc(&s[i], c);
		j++;
		i = ft_strlen_until_c(&s[i], c) + i;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (s[0] == '\0')
	{
		split = check_s((char *)s);
		return (split);
	}
	split = malloc((nb_str((char *)s, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	split = fill_split(split, (char *)s, c, i);
	return (split);
}
