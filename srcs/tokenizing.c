/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:42:21 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 21:13:47 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	move_indextoenv(char *str, int *i)
{
	if (!str)
		return ;
	if (str[*i] == '$')
		(*i)++;
	while (str[*i])
	{
		if (str[*i] == '$' || check_char(&str[*i]) != 0)
			return ;
		(*i)++;
	}
}

int	move_index_after_quote(char *str, int i, int quote)
{
	if (!str)
		return (0);
	while (str[i] && str[i] != quote)
		i++;
	if (str[i])
		i++;
	return (i);
}

void	fill_tokenized_with_quote(char **envp, char *res, char *src, int quote)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (src[i] != quote)
	{
		if (quote == 34 && src[i] == '$' && src[i + 1] != '$')
		{
			fill_env(res, &src[i], envp, &j);
			move_indextoenv(src, &i);
		}
		else
			ft_fill_char_and_increment(res, src, &i, &j);
	}
	res[j] = '\0';
}

void	tokenize_arg(char *res, char *src, t_data *data)
{
	int		i;
	int		quote;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (check_char(&src[i]) < 0)
		{
			quote = src[i];
			i++;
			fill_tokenized_with_quote(data->envp, &res[j], &src[i], quote);
			j = ft_strlen(res);
			i = move_index_after_quote(src, i, quote);
		}
		else if (src[i] == '$' && src[i + 1] != '$')
		{
			fill_env(res, &src[i], data->envp, &j);
			move_indextoenv(src, &i);
		}
		else
			ft_fill_char_and_increment(res, src, &i, &j);
	}
	res[j] = '\0';
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
		if (i > 0 && ft_strncmp(data->parsing[i - 1], "<<", 2) == 0)
		{
			res[i] = tokenize_here_doc_limiter(data->parsing[i]);
			i++;
			continue ;
		}
		res[i] = malloc((size_tokenize(data->parsing[i], data->envp) + 1)
				* sizeof(char));
		if (verif_malloc_str(res, i) == 1)
			return (NULL);
		tokenize_arg(res[i], data->parsing[i], data);
		i++;
	}
	res[i] = NULL;
	free_double_tab(data->parsing);
	return (res);
}
