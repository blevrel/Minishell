/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:15:26 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/15 10:20:51 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_char(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
		return (-1);
	if (str[i] == '\'')
		return (-2);
	if (check_redirection(str) == 1)
		return (2);
	if (check_redirection(str) == 2)
		return (3);
	if (ft_strncmp(str, ">>>", 3) == 0)
		return (4);
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		return (1);
	return (0);
}

int	check_only_redirection(char *str)
{
	int	ret;

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
	return (ret);
}
