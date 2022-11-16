/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:35:35 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 13:24:31 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_value_env(char *value)
{
	char	*res;
	int		i;
	int		j;
	int		key;

	key = 0;
	i = -1;
	j = 0;
	res = malloc(len_value_env(value) + 1 * sizeof(char));
	if (verif_malloc_str(&res, 0) == 1)
		return (NULL);
	while (value[++i])
	{
		if (value[i] == '+' && value[i + 1] == '=' && key == 0)
		{
			key = 1;
			continue ;
		}
		res[j++] = value[i];
	}
	res[j] = '\0';
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
	return (res);
}

void	replace_value(char *str, int line, t_data *data)
{
	char	*new_valuestr;

	if (check_join_value(str) == 1)
	{
		new_valuestr = new_value_env(str);
		data->envp[line] = join_value_env(new_valuestr, line, data->envp);
		free(new_valuestr);
		return ;
	}
	free(data->envp[line]);
	data->envp[line] = ft_strdup(str);
}

char	**replace_value_export(char *str, int line, char **export)
{
	char	*new_valuestr;

	if (check_join_value(str) == 1)
	{
		new_valuestr = new_value(str);
		export[line] = join_value_env(new_valuestr, line, export);
		free(new_valuestr);
		return (export);
	}
	free(export[line]);
	export[line] = ft_strdup(str);
	return (export);
}

char	**fill_new_export(char **new_exp, t_cmd *cmd, t_data *data, int i)
{
	int	j;

	j = 0;
	while (cmd->cmd[++j])
	{
		if (check_value(cmd->cmd[j]) == 0)
			new_exp = fill_new_value(new_exp, data, cmd->cmd[j], &i);
		else if (check_value(cmd->cmd[j]) == 1)
		{
			ft_print_error("minishell: export: `%s': not a valid identifier\n",
				cmd->cmd[j]);
			data->return_value = 1;
		}
	}
	new_exp[i] = NULL;
	return (new_exp);
}
