/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:44:27 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 19:30:43 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**check_limiter(char **cmd, int i)
{
	char	**res;
	int		j;

	j = count_nb_here_doc(cmd);
	if (j == 0)
		return (NULL);
	res = ft_calloc((j + 1), sizeof(char *));
	if (verif_malloc_arr(res) == 1)
		return (NULL);
	j = 0;
	while (cmd[i] != NULL && ft_strcmp(cmd[i], "|") != 0)
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
	int			j;
	static int	k = 0;
	int			nb_arg;

	j = 0;
	if (data->arg[k] == '|')
		k++;
	nb_arg = count_arg(data->arg, &k);
	res->cmd = ft_calloc((nb_arg + 1), sizeof(char *));
	if (verif_malloc_arr(res->cmd) == 1)
		return (NULL);
	res->cmd[nb_arg] = NULL;
	init_null_cmd(res, count_arg(data->arg, &k));
	res->limiter = check_limiter(data->parsing, i);
	res = fill_simple_cmd(data, res, i - 1, j);
	if (index_pipe == check_nbpipe(data->arg)
		|| check_valid_cmd_for_static_reset(data, res->cmd[0]) == 1)
		k = 0;
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
		ft_print_error("\"\" : command not found\n");
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
	nb_pipe = check_nbpipe(data->arg) + 1;
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
			free_multiple_cmd(cmd_pipe);
			return (NULL);
		}
		i++;
		nb_pipe--;
	}
	cmd_pipe[i] = NULL;
	return (cmd_pipe);
}

void	init_path_heredoc(t_data *data)
{
	int	nb_cmd;
	int	i;

	i = 0;
	nb_cmd = check_nbpipe(data->arg);
	while (nb_cmd >= 0)
	{
		if (data->cmd[i]->heredoc == 1)
			here_doc(data->cmd[i], data);
		i++;
		nb_cmd--;
	}
}
