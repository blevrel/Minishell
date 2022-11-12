/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:35:09 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/12 12:52:05 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	reset_pipe_index_if_needed(char *full_arg)
{
	int	i;

	i = 0;
	while (full_arg[i])
	{
		if (full_arg[i] == '|')
			return (1);
		if (check_char(&full_arg[i]) < 0)
			i = move_index_after_quote(full_arg, i + 1);
		else
			i++;
	}
	return (0);
}

int	reset_index_if_needed(t_data *data, int i, int trigger, char *cmd)
{
	//int	prev_char;
	//int	next_char;
	//int	len;

	//len = ft_strlen(cmd);
	if (trigger == 0)
		if (check_valid_cmd_for_static_reset(data, cmd) == 1)
			return (0);
	if (!data->arg[i] || next_non_spc_char(i, data->arg) == '\0'
		|| (check_char(&data->arg[i]) < 0 && !data->arg[i + 1]))
		return (0);
	/*while (full_arg[len])
	{
		prev_char = check_char(&full_arg[len - 1]);
		next_char = check_char(&full_arg[len + 1]);
		if (check_char(&full_arg[len]) > 1 && prev_char == next_char)
			return (1);
		len++;
	}*/
	return (1);
}

