/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:29:35 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/28 09:46:45 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_null_cmd(t_cmd *res, int nb_cmd)
{
	int	i;

	i = 0;
	res->type = NULL;
	res->file = NULL;
	res->path = NULL;
	res->limiter = NULL;
	while (i < nb_cmd)
	{
		res->cmd[i] = NULL;
		i++;
	}
}

char	**cpy_export(char **env)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(size_tab(env) * sizeof(char *));
	if (verif_malloc_arr(res) == 1)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		res[j] = ft_strdup(env[i]);
		++j;
		++i;
		if (env[i] && env[i][0] == '_')
			++i;
	}
	res[j] = NULL;
	return (res);
}

int	init_env_export(t_data *data, char **env)
{
	data->envp = dup_dp(env);
	if (!data->envp)
	{
		free(data);
		ft_putstr_fd("copy env failed", 2);
		return (1);
	}
	data->export = cpy_export(env);
	if (!data->export)
	{
		free_double_tab(data->envp);
		free_data(data);
		return (1);
	}
	data->export = sort_env(data->export);
	if (data->export == NULL)
	{
		ft_putstr_fd("sort env failed", 2);
		free_double_tab(data->envp);
		free_data(data);
		return (1);
	}
	return (0);
}

int	init_data(t_data *data, char **env)
{
	if (init_env_export(data, env) == 1)
		return (1);
	data->parsing = NULL;
	data->arg = NULL;
	data->son = NULL;
	data->cmd = NULL;
	data->pipexfd = NULL;
	data->return_value = 0;
	return (0);
}
