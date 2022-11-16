/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 07:37:05 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/16 13:05:50 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	checkerror_open(char **verif)
{
	if (check_open(&verif[0]) == 1)
	{
		if (verif[1] == NULL)
			ft_print_error("minishell: : No such file or directory\n");
		else
			ft_print_error("minishell: %s: %s\n", verif[1], strerror(errno));
		return (1);
	}
	return (0);
}

char	*dup_outfile(t_data *data, t_cmd *res, int i)
{
	free(res->outfile_append);
	free(res->outfile);
	res->outfile = NULL;
	res->outfile_append = ft_strdup(data->parsing[i + 1]);
	return (res->outfile_append);
}

int	init_file(t_cmd *res, t_data *data, int i)
{
	if (ft_strcmp(data->parsing[i], ">") == 0)
	{
		free(res->outfile);
		free(res->outfile_append);
		res->outfile_append = NULL;
		res->outfile = ft_strdup(data->parsing[i + 1]);
	}
	else if (ft_strcmp(data->parsing[i], "<") == 0)
	{
		free(res->infile);
		res->infile = ft_strdup(data->parsing[i + 1]);
	}
	else if (ft_strcmp(data->parsing[i], "<<") == 0)
	{
		free(res->infile);
		res->infile = ft_strdup("here_doc");
		res->heredoc = 1;
	}
	else
		res->outfile_append = dup_outfile(data, res, i);
	if (checkerror_open(&data->parsing[i]) == 1)
		return (1);
	return (0);
}

void	free_file(t_cmd *cmd)
{
	free(cmd->outfile);
	cmd->outfile = NULL;
	free(cmd->outfile_append);
	cmd->outfile_append = NULL;
	free(cmd->infile);
	cmd->infile = NULL;
	cmd->heredoc = 0;
}
