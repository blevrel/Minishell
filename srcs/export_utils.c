/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:54:28 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/09 15:47:17 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_value_env(char *value)
{
	int	i;
	int	res;
	int	key;

	i = 0;
	res = 0;
	key = 0;
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '+' && value [i + 1] == '=' && key == 1)
		{
			++i;
			key = 1;
			continue ;
		}
		++res;
		++i;
	}
	return (res);
}

int	len_value(char *value)
{
	int	i;
	int	res;
	int	key;

	i = 0;
	res = 0;
	key = 0;
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '$')
			++res;
		if (value[i] == '+' && value [i + 1] == '=' && key == 1)
		{
			++i;
			key = 1;
			continue ;
		}
		++res;
		++i;
	}
	return (res);
}

void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**sort_env(char **env)
{
	char	**print;
	int		i;
	int		sort_tab;

	i = 0;
	sort_tab = size_tab(env);
	print = dup_dp(env);
	if (!print)
		return (NULL);
	while (sort_tab > 1)
	{
		i = 0;
		sort_tab = size_tab(env);
		while (print[i + 1] != NULL)
		{
			if (ft_strcmp(print[i], print[i + 1]) > 0)
				swap_str(&print[i], &print[i + 1]);
			else
				sort_tab--;
			i++;
		}
	}
	free_double_tab(env);
	return (print);
}

int	search_env(char *str, char **env)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	while (env[j] != NULL)
	{
		k = 0;
		i = 0;
		while (str[k] && str[k] != '=' && str[k] != '+')
		{
			if (env[j][i] != str[k])
				break ;
			++k;
			i++;
		}
		if (str[k] == '+')
			++k;
		if (env[j][i] == str[k])
			return (j);
		++j;
	}
	return (-1);
}
