/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:35:25 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/19 03:06:53 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

int	reset_index_if_needed(char *full_arg, int i, int j)
{
	while (full_arg[i + j])
	{
		if (check_char(&full_arg[i + j]) > 1)
			return (1);
		j++;
	}
	return (0);
}

int	check_if_redirection_is_in_quotes(char *str, char *full_arg)
{
	static int	i = 0;
	int			j;

	j = ft_strlen(str);
	while (ft_strncmp(&full_arg[i], str, ft_strlen(str)) != 0)
		i++;
	if (check_char(&full_arg[i - 1]) < 0
		&& check_closing_quotes(&full_arg[i - 1]) == 0)
	{
		i += ft_strlen(str);
		if (reset_index_if_needed(full_arg, i, j) == 0)
			i = 0;
		return (1);
	}
	i += ft_strlen(str);
	if (reset_index_if_needed(full_arg, i, j) == 0)
		i = 0;
	return (0);
}

int	check_only_redirection(char *str, char *full_arg)
{
	int			ret;

	if (ft_strcmp(str, "<") == 0)
		ret = 1;
	else if (ft_strcmp(str, ">") == 0)
		ret = 1;
	else if (ft_strcmp(str, ">>") == 0)
		ret = 1;
	else if (ft_strcmp(str, "<<") == 0)
		ret = 1;
	else if (ft_strcmp(str, "|") == 0)
		ret = 2;
	else
		ret = 0;
	if (ret != 0 && check_if_redirection_is_in_quotes(str, full_arg) == 1)
		return (-1);
	return (ret);
}
