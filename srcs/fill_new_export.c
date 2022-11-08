/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:35:35 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/03 17:09:13 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*new_value(char *value)
{
	char	*res;
	int		i;
	int		j;
	int		key;

	key = 0;
	i = -1;
	j = 0;
	res = malloc(len_value(value) + 1 * sizeof(char));
	if (verif_malloc_str(&res, 0) == 1)
		return (NULL);
	while (value[++i])
	{
		if (value[i] == '$')
			res[j++] = '\\';
		if (value[i] == '+' && value[i + 1] == '=' && key == 0)
		{
			key = 1;
			continue ;
		}
		res[j++] = value[i];
	}
	res[j] = '\0';
	free(value);
	return (res);
}

void	replace_value(char *str, int line, t_data *data)
{
	if (check_join_value(str) == 1)
	{
		str = new_value(str);
		data->envp[line] = join_value_env(str, line, data->envp);
		return ;
	}
	free(data->envp[line]);
	data->envp[line] = ft_strdup(str);
}

char	**replace_value_export(char *str, int line, char **export)
{
	if (check_join_value(str) == 1)
	{
		export[line] = join_value_env(str, line, export);
		return (export);
	}
	free(export[line]);
	export[line] = ft_strdup(str);
	return (export);
}

char	**fill_new_export(char **new_exp, t_cmd *cmd, t_data *data, int i)
{
	int	j;
	int	l_env;
	int	l_exp;

	j = 0;
	while (cmd->cmd[++j])
	{
		//cmd->cmd[j] = new_value(cmd->cmd[j]);
		if (check_value(cmd->cmd[j]) == 0)
		{
			l_env = search_env(cmd->cmd[j], data->envp);
			l_exp = search_env(cmd->cmd[j], data->export);
			if (l_env >= 0)
				replace_value(cmd->cmd[j], l_env, data);
			if (l_exp >= 0)
				new_exp = replace_value_export(cmd->cmd[j], l_exp, new_exp);
			else
				new_exp[i++] = new_value(cmd->cmd[j]);
		}
		else if (check_value(cmd->cmd[j]) == 1)
			printf("minishell: export: `%s': not a valid identifier\n",
				cmd->cmd[j]);
	}
	new_exp[i] = NULL;
	return (new_exp);
}
