/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:44:27 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/02 12:00:41 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


char	**check_limiter(char **cmd)
{
	int		i;
	char	**res;
	int		j;

	i = 0;
	j = 0;
	j = count_nb_here_doc(cmd);
	if (j == 0)
		return (NULL);
	res = ft_calloc((j + 1), sizeof(char *));
	if (verif_malloc_arr(res) == 1)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i], "<<") == 0)
		{
			res[j] = ft_strdup(cmd[i + 1]);
			j++;
		}
		++i;
	}
	res[j] = NULL;
	return (res);
}

t_cmd	*init_simple_cmd(t_data *data, int i, t_cmd *res, int index_pipe)
{
	int		j;

	j = 0;
	res->cmd = malloc((nb_cmd(&data->arg[i], index_pipe) + 1) * sizeof(char *));
	//res->cmd = malloc((nb_cmd(data->arg) + 1) * sizeof(char *));
	if (verif_malloc_arr(res->cmd) == 1)
		return (NULL);
	init_null_cmd(res, nb_cmd(data->arg, index_pipe));
	res->limiter = check_limiter(data->parsing);
	res = fill_simple_cmd(data, res, i, j);
	return (res);
}

t_cmd	*init_simple_struct(t_data *data, int index_pipe, t_cmd **cmd_pipe)
{
	t_cmd	*res;
	int		i;

	res = malloc(sizeof(t_cmd));
	if (verif_malloc_t_cmd(res, index_pipe, cmd_pipe) == 1)
		return (NULL);
	i = check_index_pipe(data->arg, index_pipe);
	res = init_simple_cmd(data, i, res, index_pipe);
	if (!res->cmd)
		return (NULL);
	else if (ft_strlen(data->parsing[0]) == 0)
	{
		ft_printf("\"\" : command not found\n");
		free_simple_cmd(res);
		return (NULL);
	}
	res->path = check_path(res->cmd[0], data->envp, data);
	if (!res->path)
	{
		free_simple_cmd(res);
		return (NULL);
	}
	return (res);
}

t_cmd	**init_struct_cmd(t_data *data)
{
	int		nb_pipe;
	int		i;
	t_cmd	**cmd_pipe;

	i = 0;
	nb_pipe = check_nbpipe(data->arg);
	cmd_pipe = malloc((nb_pipe + 1) * sizeof(t_cmd *));
	if (!cmd_pipe)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (NULL);
	}
	while (nb_pipe > 0)
	{
		cmd_pipe[i] = init_simple_struct(data, i, cmd_pipe);
		if (!cmd_pipe[i])
		{
			free(cmd_pipe);
			return (NULL);
		}
		i++;
		nb_pipe--;
	}
	cmd_pipe[i] = NULL;
	return (cmd_pipe);
}
