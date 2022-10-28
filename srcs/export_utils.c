/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:54:28 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/28 09:32:23 by pirabaud         ###   ########.fr       */
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

char	**fill_new_export(char **new_exp, t_cmd *cmd, t_data *data, int i)
{
	int	j;
	int	l_env;
	int	l_exp;

	j = 1;
	while (cmd->cmd[j] != NULL)
	{
		if (check_value(cmd->cmd[j]) == 0)
		{
			l_env = search_env(cmd->cmd[j], data->envp);
			l_exp = search_env(cmd->cmd[j], data->export);
			if (l_env >= 0)
				replace_value(cmd->cmd[j], l_env, data);
			if (l_exp >= 0)
				new_exp = replace_value_export(cmd->cmd[j], l_exp, new_exp);
			else
				new_exp[i++] = ft_strdup(cmd->cmd[j]);
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n",
				cmd->cmd[j]);
		++j;
	}
	new_exp[i] = NULL;
	return (new_exp);
}
