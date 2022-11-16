/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 08:58:04 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/15 15:01:27 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*fill_pwd_env(char *pwd, int trigger)
{
	char	new_pwd[PATH_MAX];
	char	*save_old_pwd;
	char	*old_pwd;

	if (trigger == 1)
	{
		save_old_pwd = ft_strdup(pwd);
		old_pwd = ft_strjoin("OLD", save_old_pwd);
		free(save_old_pwd);
		return (old_pwd);
	}
	else
	{
		free(pwd);
		pwd = ft_strjoin("PWD=", getcwd(new_pwd, PATH_MAX));
		return (pwd);
	}
}

void	directory(t_cmd *cmd, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (size_tab(cmd->cmd) > 2)
	{
		ft_print_error("minishell: cd: too many arguments\n");
		data->return_value = 1;
	}
	else if (chdir(cmd->cmd[1]) == 0)
	{
		while (data->envp[i] && ft_strncmp(data->envp[i], "PWD", 3) != 0)
				++i;
		while (data->envp[j] && ft_strncmp(data->envp[j], "OLDPWD", 6) != 0)
				++j;
		if (data->envp[j])
		{
			free(data->envp[j]);
			data->envp[j] = fill_pwd_env(data->envp[i], 1);
		}
		if (data->envp[i])
			data->envp[i] = fill_pwd_env(data->envp[i], 0);
	}
	else
	{
		ft_print_error("minishell: %s: %s: No such file or directory\n",
			cmd->cmd[0], cmd->cmd[1]);
			data->return_value = 1;
	}
}
