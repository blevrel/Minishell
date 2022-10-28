/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_limiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 09:15:53 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/28 13:50:37 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	move_index_after_limiter(char *str, int i)
{
	while (str[i] && check_char(&str[i]) != 1)
	{
		if (check_char(&str[i]) < 0)
			i = move_index_after_quote(str, i + 1);
		else
			i++;
	}
	return (i);
}

char	*fill_limiter(char *str, char *res)
{
	int	j;
	int	quote;
	int	i;

	j = 0;
	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (check_char(&str[i]) < 0)
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
				ft_fill_char_and_increment(res, str, &i, &j);
			i++;
		}
		else
			ft_fill_char_and_increment(res, str, &i, &j);
	}
	res[j] = '\0';
	return (res);
}

char	*tokenize_here_doc_limiter(char *str)
{
	char	*res;

	res = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (verif_malloc_str(&str, 0) == 1)
		return (NULL);
	res = fill_limiter(str, res);
	return (res);
}
