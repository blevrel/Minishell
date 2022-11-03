/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 07:37:05 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/03 15:01:54 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkerror_open(char **verif, t_cmd *res)
{
	if (check_open(&verif[0]) >= 1)
	{
		if (verif[1] == NULL)
			printf("minishell: : no such file or directory\n");
		else
			printf("minishell: %s: no such file or directory\n", res->outfile);
	}
	if (check_open(&verif[0]) == 2)
		return (1);
	return (0);
}


int		init_file(t_cmd *res, t_data *data, int i)
{
	if (ft_strcmp(data->parsing[i], ">") == 0) 
	{
		free(res->infile);
		free(res->infile_append);
		res->infile_append = NULL;
		res->infile = ft_strdup(data->parsing[i + 1]);
	}
	else if (ft_strcmp(data->parsing[i], "<") == 0)
	{
		free(res->outfile);
		res->outfile = ft_strdup(data->parsing[i + 1]);
	}
	else if (ft_strcmp(data->parsing[i], "<<") == 0)
	{
		free(res->outfile);
		res->outfile = NULL;
		res->heredoc = 1;
	}
	else
	{
		free(res->infile_append);
		free(res->infile);
		res->infile = NULL;
		res->infile_append = ft_strdup(data->parsing[i + 1]);
	}
	if (checkerror_open(&data->parsing[i], res) == 1)
		return (1);
	return (0);
}

void	free_file(t_cmd *cmd)
{
	free(cmd->infile);
	cmd->infile = NULL;
	free(cmd->infile_append);
	cmd->infile_append = NULL;
	free(cmd->outfile);
	cmd->outfile = NULL;
	cmd->heredoc = 0;
}
