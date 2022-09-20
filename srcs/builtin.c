/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 08:58:04 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/19 11:19:16 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_print_end(char *str)
{
	if (ft_strcmp(str, ">") == 0 || (ft_strcmp(str, "<") == 0
			|| ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0))
		return (1);
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "&&") == 0)
		return (1);
	return (0);
}

void	echo(t_cmd *data)
{
	int	i;

	if (ft_strcmp(data->cmd[1], "-n") == 0)
	{
		i = 2;
		while (data->cmd != NULL && check_print_end(data->cmd[i]) != 1)
			ft_printf("%s", data->cmd[i++]);
	}
	else
	{
		i = 1;
		while (data->cmd != NULL && check_print_end(data->cmd[i]) != 1)
			ft_printf("%s", data->cmd[i++]);
		ft_printf("\n");
	}
}

void	pwd(void)
{
	char	buff[10000];
	
	if (getcwd(buff, 10000) == NULL)
	{
		ft_putstr_fd("error pwd", 2);
		return ;
	}
	ft_printf("%s\n", buff);
}

void	env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

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
		while(ft_strncmp(data->envp[i], "PWD", 3) != 0)
				++i;
		
		while(ft_strncmp(data->envp[j], "OLDPWD", 6) != 0)
				++j;
		free(data->envp[j]);
		old_pwd = ft_strdup(data->envp[i]);
		data->envp[j] = ft_strjoin("OLD", old_pwd);
		free(data->envp[i]);
		data->envp[i] = ft_strjoin("PWD=", getcwd(new_pwd, 10000));
		free(old_pwd);
	}
}
