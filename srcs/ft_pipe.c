/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:17:04 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/12 16:49:44 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nb_here_doc(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<<") == 0)
			count++;
		++i;
	}
	return (count);
}

void	start_child(t_data *data, int nb_pipe)
{
	int	i;

	i = 1;
	fi_pipe(data);
	while (nb_pipe > 2)
	{
		n_pipe(data, i);
		i++;
		nb_pipe--;
	}
	l_pipe(data, i);
	return_value(data->son, data, check_nbpipe(data->arg));
}

void	free_pipex(int **pipexfd, int size)
{
	int	i;

	i = 0;
	while (size > 1 && i < size)
	{
		free(pipexfd[i]);
		pipexfd[i] = 0;
		i++;
	}
	free(pipexfd);
	pipexfd = 0;
}

int	ft_pipe(t_data *data)
{
	int		nb_pipe;

	if (!data->cmd)
		return (1);
	nb_pipe = check_nbpipe(data->arg);
	data->pipexfd = malloc_pipe(nb_pipe);
	if (verif_malloc_int_arr(data->pipexfd) == 1)
		return (1);
	data->son = malloc(nb_pipe * sizeof(pid_t));
	if (!data->son)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (1);
	}
	start_child(data, nb_pipe);
	free_pipex(data->pipexfd, nb_pipe);
	return (0);
}
