/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 08:58:04 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/27 16:14:25 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	directory(t_cmd *cmd, t_data *data)
{
	char	new_pwd[1000];
	char	*old_pwd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (chdir(cmd->cmd[1]) == 0)
	{
		while (ft_strncmp(data->envp[i], "PWD", 3) != 0)
				++i;
		while (ft_strncmp(data->envp[j], "OLDPWD", 6) != 0)
				++j;
		free(data->envp[j]);
		old_pwd = ft_strdup(data->envp[i]);
		data->envp[j] = ft_strjoin("OLD", old_pwd);
		free(data->envp[i]);
		data->envp[i] = ft_strjoin("PWD=", getcwd(new_pwd, 10000));
		free(old_pwd);
	}
}
