/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 08:30:58 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 13:25:57 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_value(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_' && (str[i + 1] == '\0' || str[i + 1] == '='))
		return (2);
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (ft_isalnum(str[i]) == 0 && str[i] != ' '
			&& str[i] != '_')
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
		if (search_env(cmd[i], env) == -1 && check_value(cmd[i]) == 0)
			++res;
		++i;
	}
	return (res);
}

char	**new_export(t_cmd *cmd, t_data *data)
{
	char	**new_export;
	int		nb_new;

	nb_new = check_new_export(cmd->cmd, data->envp);
	new_export = malloc((nb_new + size_tab(data->export) + 1) * sizeof(char *));
	if (!new_export)
	{
		ft_putstr_fd("error malloc", 2);
		return (NULL);
	}
	new_export = cpy_tab(new_export, data->export);
	new_export = fill_new_export(new_export, cmd, data, size_tab(data->export));
	new_export = sort_env(new_export);
	free_double_tab(data->export);
	return (new_export);
}

char	**fill_new_value(char **new_exp, t_data *data, char *value, int	*i)
{
	int	new;

	new = search_env(value, data->envp);
	if (new >= 0)
		replace_value(value, new, data);
	new = search_env(value, data->export);
	if (new >= 0)
		new_exp = replace_value_export(value, new, new_exp);
	else
		new_exp[(*i)++] = new_value(value);
	return (new_exp);
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
