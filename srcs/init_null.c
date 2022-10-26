/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:29:35 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/25 10:34:24 by pirabaud         ###   ########.fr       */
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
	//check_malloc
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

void	init_data(t_data *data, char **env)
{
	data->envp = dup_dp(env);
	data->export = cpy_export(env);
	data->export = sort_env(data->export);
	data->parsing = NULL;
	data->arg = NULL;
	data->son = NULL;
	data->cmd = NULL;
	data->pipexfd = NULL;
	data->return_value = 0;
}
