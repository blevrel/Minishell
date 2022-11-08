/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_echo_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:24:49 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/08 11:43:42 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_multiple_options(char *res)
{
	int	i;

	i = 0;
	if (!res || !res[0] || ft_strlen(res) < 2)
		return (1);
	while (res[i] && res[i + 1] && res[i] == '-' && res[i + 1] != '-')
	{
		i++;
		while (res[i] == 'n')
			i++;
	}
	if (res[i])
		return (1);
	return (0);
}

int	get_cmd_join_size(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (is_valid_option(cmd, i) == 0)
			count += ft_strlen(cmd[i]);
		else
			return (count);
		i++;
	}
	return (count);
}

int	join_option_is_doable(char c, char *full_arg, int *j)
{
	int	ret;

	ret = 0;
	while (full_arg[*j] && full_arg[*j] != c)
		(*j)++;
	if (*j != 0 && check_char(&full_arg[*j - 1]) == 1)
		ret = 1;
	while (full_arg[*j] && check_char(&full_arg[*j]) == 0)
		(*j)++;
	if (c == '-')
		ret = 0;
	return (ret);
}

char	*join_echo_options(char **cmd, char *full_arg)
{
	int		i;
	int		j;
	char	*res;
	int		trigger;

	i = 1;
	j = 0;
	res = ft_calloc((get_cmd_join_size(cmd) + 1), sizeof(char));
	if (verif_malloc_str(&res, 0) == 1)
		return (NULL);
	while (cmd[i])
	{
		trigger = 0;
		if (join_option_is_doable(cmd[i][0], full_arg, &j) == 0)
			trigger = 1;
		if (is_valid_option(cmd, i) == 0 && trigger == 1)
			res = join_gnl(res, cmd[i]);
		else
			return (res);
		i++;
	}
	return (res);
}

int	check_echo_option(char *full_arg, char **cmd)
{
	char	*res;

	res = join_echo_options(cmd, full_arg);
	if (check_multiple_options(res) == 1)
	{
		free(res);
		return (1);
	}
	if (check_option_format(full_arg, res) == 1)
	{
		free(res);
		return (1);
	}
	free(res);
	return (0);
}
