/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:35:25 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/12 16:39:04 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strncmp_skip_quotes(char *s1, char *s2, size_t len)
{
	size_t	i;
	int		j;
	int		k;

	i = 0;
	if (s2[i] == '\0')
		return (0);
	while (s2[i] != '\0' && i < len)
	{
		j = 0;
		k = 0;
		while (s1[i + k] == s2[j] && s1 && i < len)
		{
			i++;
			j++;
			if (check_char(&s1[i + k]) < 0 && s1[i + k] != s2[j])
				k += count_index_after_quote(&s1[i + k]);
			if (s2[j] == '\0')
				return (0);
		}
		i = i - j + 1;
	}
	return (1);
}

int	check_redirection(char *str)
{
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (2);
	else
		return (0);
}

int	check_if_redirection_is_in_quotes(char *str, char *full_arg, int *i)
{
	int			j;

	j = ft_strlen(str);
	while (ft_strncmp_skip_quotes(&full_arg[*i], str, j) != 0)
		(*i)++;
	if (*i == 0)
		return (0);
	if (check_char(&full_arg[*i - 1]) < 0
		&& check_closing_quotes(&full_arg[*i - 1]) == 0)
	{
		*i += j;
		if (check_only_redirection(str) == 1)
			*i = move_to_end_of_arg(full_arg, *i);
		return (1);
	}
	*i += j;
	if (check_only_redirection(str) == 1)
		*i = move_to_end_of_arg(full_arg, *i);
	return (0);
}

int	move_index_redirection(char *full_arg, char *str, int i)
{
	int	j;
	
	j = ft_strlen(str);
	while (ft_strncmp_skip_quotes(&full_arg[i], str, j) != 0)
		i++;
	if (j == 0)
	{
		while (ft_strncmp(&full_arg[i], "\"\"", 2) != 0)
			i++;
		i += 2;
	}
	else
	{
		i += j;
		while (full_arg[i] && (check_char(&full_arg[i]) < 1
			|| check_closing_quotes(&full_arg[i]) == 1))
		{
			if (check_char(&full_arg[i]) < 0
				&& check_closing_quotes(&full_arg[i]) == 0)
				i = move_index_after_quote(full_arg, i);
			else
				i++;
		}
	}
	return (i);
}

int	get_arg_type(t_data *data, char *str, char *full_arg, int trigger)
{
	int			ret;
	static int	i = 0;

	ret = check_only_redirection(str);
	if (ret != 0 && check_if_redirection_is_in_quotes(str, full_arg, &i) == 1)
		return (-1);
	if (ret != 2 && ret != 1)
		i = move_index_redirection(full_arg, str, i);
	if (reset_index_if_needed(data, i, trigger, str) == 0)
		i = 0;
	return (ret);
}
