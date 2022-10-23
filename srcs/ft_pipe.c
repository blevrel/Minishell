/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:48:40 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/20 11:28:21 by blevrel          ###   ########.fr       */
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


int	ft_pipe(t_data *data)
{
	int		nb_pipe;
	int		i;

	i = 1;
	nb_pipe = check_nbpipe(data->arg);
	if (!data->cmd)
		return (1);
	data->pipexfd = malloc_pipe(nb_pipe);
	if (data->pipexfd == 0)
		return (0);
	data->son = malloc(nb_pipe * sizeof(pid_t));
	if (!data->son)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (1);
	}
	fi_pipe(data);
	while (nb_pipe > 2)
	{
		n_pipe(data, i);
		i++;
		nb_pipe++;
	}
	l_pipe(data, i);
	return_value(data->son, data, check_nbpipe(data->arg));
	return (0);
}
