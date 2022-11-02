/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:54:28 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/02 16:23:25 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	j = 0;
	while (env[j] != NULL)
	{
		i = 0;
		while (env[j][i] && env[j][i] != '=')
				++i;
		if (ft_strncmp(str, env[j], i) == 0)
		{
			while (str[i] && str[i] != '=' && str[i] != '+')
					++i;
			if (ft_strncmp(str, env[j], i) == 0)
				return (j);
		}
		++j;
	}
	return (-1);
}
