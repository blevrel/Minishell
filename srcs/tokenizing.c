/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:42:21 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/14 10:48:10 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	fill_tokenized_with_quote(t_data *data, char *res, char *src)
{
	int	j;
	int	i;
	int	quote;

	i = 1;
	j = 0;
	quote = src[0];
	while (src[i] != quote)
	{
		if (quote == 34 && src[i] == '$'
			&& (ft_isalnum(src[i + 1]) == 8 || src[i + 1] == '?'))
		{
			if (fill_env(res, &src[i], data, &j) == 1)
				return (1);
			i = move_indextoenv(src, i);
		}
		else
			ft_fill_char_and_increment(res, src, &i, &j);
	}
	res[j] = '\0';
	return (0);
}

int	fill_tokenize_arg(char *res, char *src, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (check_char(&src[i]) < 0)
		{
			fill_tokenized_with_quote(data, &res[j], &src[i]);
			j = ft_strlen(res);
			i = move_index_after_quote(src, i);
		}
		else if (src[i] == '$' && ((ft_isalnum(src[i + 1]) != 0
					&& src[i + 1] != '\0') || src[i + 1] == '?'))
		{
			if (fill_env(res, &src[i], data, &j) == 1)
				return (1);
			i = move_indextoenv(src, i);
		}
		else
			ft_fill_char_and_increment(res, src, &i, &j);
	}
	res[j] = '\0';
	return (0);
}

char	*tokenizing_arg(t_data *data, int i)
{
	char	*res;

	if (i > 0 && ft_strncmp(data->parsing[i - 1], "<<", 2) == 0)
	{
		res = tokenize_here_doc_limiter(data->parsing[i]);
		return (res);
	}
	res = malloc((size_tokenize(data->parsing[i], data->envp, data) + 1)
			* sizeof(char));
	if (!res)
	{
		ft_putstr_fd("Malloc failed", 2);
		return (NULL);
	}
	if (fill_tokenize_arg(res, data->parsing[i], data) == 1)
		return (NULL);
	return (res);
}

char	**tokenizing(t_data *data)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc((size_tab(data->parsing) + 1) * sizeof (char *));
	if (verif_malloc_arr(res))
		return (NULL);
	while (data->parsing[i] != NULL)
	{
		res[i] = tokenizing_arg(data, i);
		if (!res[i])
		{
			free_double_tab(res);
			free_double_tab(data->parsing);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	free_double_tab(data->parsing);
	return (res);
}
