/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:55:56 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/27 15:56:22 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
