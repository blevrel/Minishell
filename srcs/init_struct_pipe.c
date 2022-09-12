/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:44:27 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/12 10:31:05 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_null_cmd(t_cmd *res)
{
	res->type = NULL;
	res->file = NULL;
}

void	init_file(t_cmd *res, t_data *data, int i)
{
	if (!res->type)
		free(res->type);
	res->type = ft_strdup(data->cmd[i]);
	if (!res->file)
		free(res->file);
	res->file = ft_strdup(data->cmd[i + 1]);
	check_open(&data->cmd[i]);
}

void	init_simple_cmd(t_data *data, t_cmd *res, int i)
{
	int	j;

	j = 0;
	res->cmd = malloc((nb_cmd(data->cmd, i) + 1) * sizeof(char *));
	if (!res->cmd)
	{
		ft_putstr_fd("error malloc", 2);
		return ;
	}
	init_null_cmd(res);
	while (data->cmd[i] != NULL && ft_strcmp(data->cmd[i], "|"))
	{
		if (check_redirection_pipe(data->cmd[i]) == 1)
		{
			init_file(res, data, i);
			if (ft_strcmp(data->cmd[i], "<<") != 0)
				i = i + 2;
		}
		else
			res->cmd[j++] = ft_strdup(data->cmd[i++]);
	}
	res->cmd[j] = NULL;
}

t_cmd	*init_simple_struct(t_data *data, int index_pipe)
{
	t_cmd	*res;
	int		i;

	i = check_index_pipe(data->cmd, index_pipe);
	res = malloc(sizeof(t_cmd));
	init_simple_cmd(data, res, i);
	if (!res->cmd)
		return (NULL);
	return (res);
}

t_cmd	**init_struct_pipe(t_data *data)
{
	int		nb_pipe;
	int		i;
	t_cmd	**cmd_pipe;

	i = 0;
	nb_pipe = check_nbpipe(data->cmd);
	cmd_pipe = malloc((nb_pipe + 1) * sizeof(t_cmd *));
	if (!cmd_pipe)
	{
		ft_putstr_fd("error malloc\n", 2);
		return (NULL);
	}
	while (nb_pipe >= 0)
	{
		cmd_pipe[i] = init_simple_struct(data, i);
		cmd_pipe[i]->path = check_path(cmd_pipe[i]->cmd[0], data->envp);
		i++;
		--nb_pipe;
	}
	return (cmd_pipe);
}
