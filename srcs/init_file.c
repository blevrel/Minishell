/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 07:37:05 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/02 14:07:54 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checkerror_open(char **verif, t_cmd *res)
{
	if (check_open(&verif[0]) == 1)
	{
		if (verif[1] == NULL)
			printf("minishell: : no such file or directory\n");
		else if (!res->cmd[0])
			printf("minishell: %s: no such file or directory\n", res->outfile);
		else
			printf("%s: %s: no such file or directory\n",
				res->cmd[0], verif[1]);
	}
}


void	init_file(t_cmd *res, t_data *data, int i)
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
		res->heredoc = 1;
	else
	{
		free(res->infile_append);
		free(res->infile);
		res->infile = NULL;
		res->infile_append = ft_strdup(data->parsing[i + 1]);
	}
	checkerror_open(&data->parsing[i], res);
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
