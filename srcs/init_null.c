/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:29:35 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/11 10:01:01 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_null_cmd(t_cmd *res)
{
	res->type = NULL;
	res->file = NULL;
	res->path = NULL;
	res->limiter = NULL;
}

void	init_data(t_data *data, char **env)
{
	data->envp = dup_dp(env);
	data->export = dup_dp(env);
	data->export = sort_env(data->export);
	data->parsing = NULL;
	data->arg = NULL;
	data->son = NULL;
	data->cmd = NULL;
	data->pipexfd = NULL;
}
