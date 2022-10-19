/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 08:30:58 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/18 22:08:19 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_value(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0)
		return (1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '=')
			return (1);
		++i;
	}
	return (0);
}

int	check_new_export(char **cmd, char **env)
{
	int	i;
	int	res;

	i = 1;
	res = 0;
	while (cmd[i] != NULL)
	{
		if (search_env(cmd[i], env) == -1)
			++res;
		++i;
	}
	return (res);
}

char	**replace_value_export(char *str, int line, char **export)
{
	free(export[line]);
	export[line] = ft_strdup(str);
	return (export);
}

char	**new_export(t_cmd *cmd, t_data *data)
{
	char	**new_export;
	int		nb_new;

	nb_new = check_new_export(cmd->cmd, data->envp);
	new_export = malloc((nb_new + size_tab(data->export) + 1) * sizeof(char *));
	if (verif_malloc_arr(new_export) == 1)
		return (NULL);
	new_export = cpy_tab(new_export, data->export);
	new_export = fill_new_export(new_export, cmd, data, size_tab(data->export));
	new_export = sort_env(new_export);
	free_double_tab(data->export);
	return (new_export);
}

void	ft_export(t_cmd *cmd, t_data *data)
{
	if (cmd->cmd[1] == NULL)
	{
		print_export(data->export);
		return ;
	}
	data->export = new_export(cmd, data);
	if (search_new_env(cmd->cmd, data->envp) > 0)
		data->envp = new_env_export(cmd->cmd, data->envp);
}
