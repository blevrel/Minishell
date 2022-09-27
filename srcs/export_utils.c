/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:54:28 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/26 09:28:23 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_str(char **s1, char **s2)
{
	char *tmp;
	
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**sort_env(char **env)
{
	char **print;
	int	i;
	int	sort_tab;

	i = 0;
	sort_tab = size_tab(env);
	print = dup_dp(env);
	while (sort_tab > 1)
	{
		i = 0;
		sort_tab = size_tab(env);
		while (print[i + 1] != NULL)
		{
			if (ft_strcmp(print[i], print[i + 1]) > 0)
			{
				swap_str(&print[i], &print[i + 1]);
				i++;
			}
			else
			{
				i++;
				--sort_tab;
			}
		}
	}
	free_double_tab(env);
	return (print);
}

void	print_export(char	**print)
{
	int	i;
	
	i = 0;
	while(print[i] != NULL)
	{
		printf("declare -x \"%s\"\n", print[i]);
		i++;
	}
}

int	search_env(char *str, char **env)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while(str[i] && str[i] != '=')
		++i;
	if (str[i] != '=')
		return (-1);
	while(env[j] != NULL)
	{
		if(ft_strncmp(str, env[j], i) == 0)
			return (j);
		++j;
	}
	return (-1);
}

char	**fill_new_export(char **new_export, t_cmd *cmd, t_data *data, int i)
{
	int	j;
	int	err;
	
	err = 0;
	j = 1;
	while (cmd->cmd[j] != NULL)
	{
		if (check_value(cmd->cmd[j]) == 0)
		{
			if (search_env(cmd->cmd[j], data->envp) >= 0 && err != 1)
				replace_value(cmd->cmd[j], search_env(cmd->cmd[j], data->envp), data);
			if (search_env(cmd->cmd[j], new_export) >= 0 && err != 1)
				new_export = replace_value_export(cmd->cmd[j], search_env(cmd->cmd[j], new_export), new_export);
			else
				new_export[i++] = ft_strdup(cmd->cmd[j]);
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n", cmd->cmd[j]);
		++j;
	}
	new_export[i] = NULL;
	new_export = sort_env(new_export);
	return (new_export);
}
